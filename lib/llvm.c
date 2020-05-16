
#include <lib/llvm.h>

// The module and the builder are unique
// in processing one file, so they're global.
static LLVMModuleRef module;
static LLVMBuilderRef builder;

// Maintain the current basic block and function reference.
static LLVMBasicBlockRef cur_bblock;
static LLVMValueRef cur_func;

// Record the number of members in current processing struct.
static int member_num;

// Get the symbol table from the semantic module.
extern symbol_table stab;

static void gen_var_list(ast_node* T);
static void gen_struct(ast_node* T);
static void gen_expr(ast_node* T);
static void gen_all(ast_node* T);

// Allocate and return a new basic block alias.
static char* new_bblock() {
  static int cnt = 0;
  static char tmp[MAX_ALIAS_LEN] = {0};
  sprintf(tmp, ".BB%d", cnt);
  cnt++;
  return tmp;
}

// Allocate and return a new load alias.
static char* new_load() {
  static int cnt = 0;
  static char tmp[MAX_ALIAS_LEN] = {0};
  sprintf(tmp, "L%d", cnt);
  cnt++;
  return tmp;
}

static void gen_var_list(ast_node* T) {
  LLVMTypeRef type;

  switch (T->type) {

  // We use the external field here to classify external
  // and local definitions in order to save space.
  case EXT_DECL_LIST:
    T->children[0]->external = T->children[1]->external = 1;

  case DEC_LIST:

    // T->num may represent the index of member
    // so we need to pass it down to children. 
    T->children[0]->num = T->num;
    T->children[1]->num = T->num + 1;
    gen_var_list(T->children[0]);
    gen_var_list(T->children[1]);
    break;

  // Store the llvm type of this variable in the symbol
  // table. (Use the information in the symbol table to
  // produce)
  case IDENT:
    type = LLVM_TYPE(
      SYMBOL(T->symbol).dtype, SYMBOL(T->symbol).struct_type);

    // If the variable is an array, we need to build
    // an array type here.
    for (int i = T->dim-1; i >= 0; i--)
      type = LLVMArrayType(type, T->capacity[i]);
    SYMBOL(T->symbol).llvm_type = type;

    // If T->parent_struct is not null, T should
    // be a member instead of variable.
    //
    // T->num represents the index of member
    // and we record it in the param_num field in
    // the symbol table.
    if (T->parent_struct)
      SYMBOL(T->symbol).param_num = T->num;

    // Elsewise this variable should be initialized.
    else if (T->external) {
      // Initialize the global variable.
      SYMBOL(T->symbol).llvm_value = LLVMAddGlobal(
        module, type, SYMBOL(T->symbol).alias);
      // Initialize the local variable.
    } else SYMBOL(T->symbol).llvm_value = LLVMBuildAlloca(
      builder, type, SYMBOL(T->symbol).alias
    );

    break;
  
  // Set the initializer of variables.
  case VAR_INIT:
    gen_var_list(T->children[0]);
    gen_expr(T->children[1]);

    // Initialize global variable.
    if (T->children[0]->external)
      LLVMSetInitializer(
        SYMBOL(T->children[0]->symbol).llvm_value,
        T->children[1]->llvm_value);
    
    // Initilaize local variable.
    else LLVMBuildStore(builder, T->children[1]->llvm_value,
      SYMBOL(T->children[0]->symbol).llvm_value);

    break;
  }
}

static void gen_struct(ast_node* T) {

  // Define a struct and declear corresponding
  // variables right away.
  if (T->children[0]) {
    T->llvm_type = LLVMStructCreateNamed(
      LLVMGetGlobalContext(), SYMBOL(T->symbol).alias);

    // Add the member list to the struct.
    T->children[0]->llvm_argtypes = 
      LIST_NEW(type_list, LLVMTypeRef);
    gen_all(T->children[0]);
    T->children[0]->num++;
    LLVMStructSetBody(
      T->llvm_type, T->children[0]->llvm_argtypes->arr,
      T->children[0]->num, 0
    );

    // Set the llvm type in the symbol table.
    SYMBOL(T->symbol).llvm_type = T->llvm_type;

  // Use a pre-defined struct.
  } else {
    T->llvm_type = SYMBOL(T->symbol).llvm_type;
  }
}

static void gen_expr(ast_node* T) {
  LLVMValueRef indices[MAX_INDICE_NUM] = {0};

  if (T) switch (T->type) {

  // Identifiers.
  case IDENT:

    // If T->llvm_value is not null, this is an
    // assignment and we need to update the value
    // in the symbol table.
    if (T->llvm_value) {
      LLVMBuildStore(builder, T->llvm_value,
        SYMBOL(T->symbol).llvm_value);

    // Elsewise we're trying to get the value of
    // a variable.
    } else {

      // If the variable is a parameter, we need to
      // get the parameter from function.
      if (SYMBOL(T->symbol).stype == PARAM) {
        T->llvm_value = LLVMGetParam(
          SYMBOL(T->symbol).llvm_value,
          SYMBOL(T->symbol).param_num);
        
        // For convinience, we put the parameter on
        // stack and regard it as a variable from now on.
        SYMBOL(T->symbol).llvm_value = LLVMBuildAlloca(
          builder, SYMBOL(T->symbol).llvm_type,
          SYMBOL(T->symbol).alias
        );
        LLVMBuildStore(builder, T->llvm_value, 
          SYMBOL(T->symbol).llvm_value);
        SYMBOL(T->symbol).stype = VAR;

      // Not parameter, just load the variable from stack.
      } else T->llvm_value = LLVMBuildLoad(builder,
          SYMBOL(T->symbol).llvm_value, new_load());
    }
    break;

  // Literals.
  case L_INT:
    T->llvm_value = LLVMConstInt(
      LLVMInt32Type(), T->value.itg, 1);
    break;
  case L_CHAR:
    T->llvm_value = LLVMConstInt(
      LLVMInt8Type(), T->value.itg, 0);
    break;
  case L_FLOAT:
    T->llvm_value = LLVMConstReal(
      LLVMFloatType(), T->value.flt);
    break;
  case L_STRING:
    T->llvm_value = LLVMConstString(
      T->value.str, strlen(T->value.str), 0);
    break;

  // Assigning.
  case ASSIGN:

    // We calculate the value of assigner and pass it
    // to the assignee.
    gen_expr(T->children[1]);
    T->children[0]->llvm_value = T->children[1]->llvm_value; 
    gen_expr(T->children[0]);
    break;

  case COMP_ASSIGN:

    // In composed assignments, we need to do an operation
    // between assigner and assignee first, and then pass
    // the result to the assignee.
    gen_expr(T->children[0]);
    gen_expr(T->children[1]);
    T->children[0]->llvm_value = 
      LLVM_BUILD_COMP(builder, T->value.str, 
        T->children[0]->llvm_value,
        T->children[1]->llvm_value,
        SYMBOL(T->symbol).alias);
    
    // The second recursion to pass the result.
    gen_expr(T->children[0]);
    break;

  // Logic expressions.
  case OP_AND:
  case OP_OR:
  case OP_G:
  case OP_L:
  case OP_GE:
  case OP_LE:
  case OP_EQ:
  case OP_NEQ:
    gen_expr(T->children[0]);
    gen_expr(T->children[1]);
    T->llvm_value = LLVM_BUILD_BIN(builder, T->type, T->children[0]->llvm_value,
      T->children[1]->llvm_value, SYMBOL(T->symbol).alias);
    break;

  // Arithmetic expressions.
  case OP_ADD:
  case OP_SUB:
  case OP_STAR:
  case OP_DIV:
  case OP_MOD:
    gen_expr(T->children[0]);
    gen_expr(T->children[1]);
    T->llvm_value = LLVM_BUILD_BIN(builder, T->type, T->children[0]->llvm_value,
      T->children[1]->llvm_value, SYMBOL(T->symbol).alias);
    break;

  // Single-operand expressions.
  case OP_DEC:
  case OP_INC:
  case OP_NOT:
  case UMINUS:
    gen_expr(T->children[0]);
    T->llvm_value = LLVM_BUILD_UN(builder, T->type,
      T->children[0]->llvm_value, SYMBOL(T->symbol).alias);
    
    // Store the results of increment or decrement.
    if (T->type == OP_INC || T->type == OP_DEC)
      LLVMBuildStore(builder, T->llvm_value,
        SYMBOL(T->children[0]->symbol).llvm_value);
    break;

  case MEMBER_CALL:
    if (T->children[0]->type != IDENT)
      gen_expr(T->children[0]);

    // Load the address of this member if not exist.
    if (!SYMBOL(T->symbol).llvm_value)
      SYMBOL(T->symbol).llvm_value = LLVMBuildStructGEP(
        builder, SYMBOL(T->children[0]->symbol).llvm_value,
        SYMBOL(stab_search(T->value.str)).param_num,
        SYMBOL(T->parent_struct).alias);

    // If T->llvm_value is not null, we're going to
    // assign a value to this member.
    if (T->llvm_value) {
      LLVMBuildStore(builder, T->llvm_value,
        SYMBOL(T->symbol).llvm_value);
    
    // Elsewise, we're going to load the value of it.
    } else {
      T->llvm_value = LLVMBuildLoad(builder,
        SYMBOL(T->symbol).llvm_value, new_load());
    }
    break;

  // Function calls.
  case FUNC_CALL:
    if (T->children[0]) {
      T->children[0]->llvm_args = LIST_NEW(value_list, LLVMValueRef);
      gen_expr(T->children[0]);
    }

    T->llvm_value = LLVMBuildCall(
      builder, LLVMGetNamedFunction(module,
      SYMBOL(stab_search(T->value.str)).name),
      T->children[0]->llvm_args->arr,
      T->children[0]->num,
      SYMBOL(T->symbol).alias
    );
    break;

  // Argument list.
  case ARG_LIST:
    gen_expr(T->children[0]);
    LIST_PUSH(T->llvm_args, T->children[0]->llvm_value, LLVMValueRef);

    if (T->children[1]) {
      T->children[1]->llvm_args = T->llvm_args;
      gen_expr(T->children[1]);
      T->num = T->children[1]->num + 1;
    } else T->num = 1;
    break;
  
  case ARRAY_CALL:
    gen_expr(T->children[0]);
    gen_expr(T->children[1]);

    // Get the address of the indexed element.
    indices[0] = LLVMConstInt(LLVMInt64Type(), 0, 0);
    indices[1] = T->children[1]->llvm_value;
    SYMBOL(T->symbol).llvm_value = LLVMBuildGEP(builder, 
      SYMBOL(T->children[0]->symbol).llvm_value,
      indices, 2, new_load());

    // If T->llvm_value is not null, this is an
    // assignment and we need to update the value
    // of corresponding element in array.
    if (T->llvm_value) {
      LLVMBuildStore(builder,
        T->llvm_value, SYMBOL(T->symbol).llvm_value);

    // Elsewise we're trying to get the value of
    // this element.
    } else {
      T->llvm_value = LLVMBuildLoad(builder, 
        SYMBOL(T->symbol).llvm_value, new_load());
    }
    break;
  }
}

void gen_all(ast_node* T) {
  LLVMBasicBlockRef bbefore, btrue, bfalse, bafter;

  if (T) switch (T->type) {
  case EXT_DEF_LIST:
    if (T->children[0]) {
      gen_all(T->children[0]);
      if (T->children[1])
        gen_all(T->children[1]);
    }
    break;

  // Handle variable declarations. Don't forget to
  // deal with struct types.
  case EXT_VAR_DEF:
    T->children[1]->external = 1;
  case VAR_DEF:
    if (T->children[0]->type == T_STRUCT)
      gen_struct(T->children[0]);
    gen_var_list(T->children[1]);
    break;
  
  case STRUCT_DEF:

    // We create the named struct type beforehand.
    T->llvm_type = LLVMStructCreateNamed(
      LLVMGetGlobalContext(), SYMBOL(T->symbol).alias);

    // Collect the type of members in a type_list
    // and set the body of struct with it.
    if (T->children[0]) {
      T->children[0]->llvm_argtypes = 
        LIST_NEW(type_list, LLVMTypeRef);
      gen_all(T->children[0]);
      LLVMStructSetBody(
        T->llvm_type, T->children[0]->llvm_argtypes->arr,
        member_num, 0
      );
    } 

    // Record the generated struct type in the
    // symbol table.
    SYMBOL(T->symbol).llvm_type = T->llvm_type;
    break;

  case MEMBER_LIST:

    // Handle nested struct.
    if (T->children[0]->type == T_STRUCT)
      gen_struct(T->children[0]);

    // Because this line of members has the same
    // type, we just need to use the T->num generated
    // by the semantic analysis to get their types.
    for (int i = 0; i < T->children[1]->num; i++)
      LIST_PUSH(T->llvm_argtypes,
        LLVM_TYPE(T->children[0]->type, T->children[0]->symbol),
        LLVMTypeRef);
    
    // Pass the list of types downward to the next
    // line of members and accumulate the number of
    // members.
    if (T->children[2]) {
      T->children[2]->llvm_argtypes = T->llvm_argtypes;
      T->children[2]->num = T->num + T->children[1]->num;
      gen_all(T->children[2]);
    
    // If wer're at the end of list, record the number
    // of members in the global variable.
    } else member_num = T->num + T->children[1]->num;

    // After that, we need to register the index in the
    // parent struct of each member's symbol table entry.
    // We need to leverage T->children[1]->num to do this.
    //
    // Set T->children[1]->num to the first member's index
    // of this line.
    T->children[1]->num = T->num;
    gen_var_list(T->children[1]);

    break;
  
  case FUNC_DEF:

    // Record the return type of function in FUNC_DECL's
    // llvm_type, which would be used to create the function.
    T->children[1]->llvm_type = 
      LLVM_TYPE(T->children[0]->type, T->children[0]->symbol);
    gen_all(T->children[1]);

    // Process the function body.
    gen_all(T->children[2]);
    if (!LLVMGetBasicBlockTerminator(cur_bblock))
      LLVMBuildRetVoid(builder);
    break;

  case FUNC_DECL:

    // We need to traverse the parameter list for
    // two times: one for collecting the parameter types,
    // one for setting the value of arguments.
    if (T->children[0]) {

      // Use a type_list to collect parameter types.
      T->children[0]->llvm_argtypes = LIST_NEW(type_list, LLVMTypeRef);
      gen_all(T->children[0]);

      // Create the function with collected information.
      // T->llvm_type was originally the type of return
      // value, but replaced with the type of function here.
      T->llvm_type = LLVMFunctionType(
        T->llvm_type, T->children[0]->llvm_argtypes->arr,
        T->children[0]->num, 0);
      
      // Add the function to the module.
      T->children[0]->llvm_value = LLVMAddFunction(module, 
        SYMBOL(T->symbol).name, T->llvm_type);
      T->llvm_value = T->children[0]->llvm_value;

      // Set current function and start a new basic block.
      cur_func = T->llvm_value;
      cur_bblock = LLVMAppendBasicBlock(cur_func, LLVM_ENTRY_LABEL);
      LLVMPositionBuilderAtEnd(builder, cur_bblock);

      // The second traverse, record parameters to the
      // symbol table and store them in the fuunction stack.
      T->children[0]->num = 0;
      gen_all(T->children[0]);

    // No parameters, the task is much easier this way.
    } else {
      T->llvm_type = LLVMFunctionType(T->llvm_type, NULL, 0, 0);
      T->llvm_value = LLVMAddFunction(module, 
        SYMBOL(T->symbol).name, T->llvm_type);

      // Set current function and start a new basic block.
      cur_func = T->llvm_value;
      cur_bblock = LLVMAppendBasicBlock(cur_func, LLVM_ENTRY_LABEL);
      LLVMPositionBuilderAtEnd(builder, cur_bblock);
    }
    break;
  
  case PARAM_LIST:

    // If T->llvm_value is not null, we're in the
    // second traverse in which we pass the function
    // type down to children.
    if (T->llvm_value) {
      T->children[0]->llvm_value = T->llvm_value;

      // This is the `T->num`th parameter of function,
      // such information would be used for extracting
      // the corresponding parameter.
      T->children[0]->num = T->num;
      gen_all(T->children[0]);

      // We accumulate T->num during the recursion.
      if (T->children[1]) {
        T->children[1]->llvm_value = T->llvm_value;
        T->children[1]->num = T->num + 1;
        gen_all(T->children[1]);
      }
    
    // Elsewise, we're in the first traverse in which
    // we collect the parameter type information for
    // creating the function.
    } else {
      T->children[0]->llvm_argtypes = T->llvm_argtypes;
      gen_all(T->children[0]);

      // In this traverse the T->num has the different
      // meaning with the second traverse: it represents
      // the number of parameters of function.
      if (T->children[1]) {
        T->children[1]->llvm_argtypes = T->llvm_argtypes;
        gen_all(T->children[1]);
        T->num = T->children[1]->num + 1;
      } else T->num = 1;
    }
    break;
  
  case PARAM_DEC:

    // If T->llvm_value is not null, we're in the
    // second traverse in which we record the value
    // of function in the symbol table.
    if (T->llvm_value) {
      SYMBOL(T->children[1]->symbol).llvm_value = T->llvm_value;
      SYMBOL(T->children[1]->symbol).llvm_type = 
        LLVM_TYPE(T->children[0]->type, T->children[0]->symbol);
      SYMBOL(T->children[1]->symbol).param_num = T->num;
      SYMBOL(T->children[1]->symbol).stype = PARAM;

      // Store the parameter on the stack.
      gen_expr(T->children[1]);
    
    // Elsewise, we're in the first traverse in which
    // we collect the parameter type information for
    // creating the function.
    } else {
      if (T->children[0]->type == T_STRUCT)
        gen_struct(T->children[0]);

      LIST_PUSH(T->llvm_argtypes, 
        LLVM_TYPE(T->children[0]->type, T->children[0]->symbol),
        LLVMTypeRef);
    }
    break;

  // Nothing special to do with code blocks or statement list.
  case CODE_BLOCK:
    if (T->children[0]) {
      T->children[0]->llvm_before = T->llvm_before;
      T->children[0]->llvm_after = T->llvm_after;
      gen_all(T->children[0]);
    }
    break;
  
  case STMT_LIST:
    if (T->children[0]) {
      T->children[0]->llvm_before = T->llvm_before;
      T->children[0]->llvm_after = T->llvm_after;
      gen_all(T->children[0]);
    }
    if (T->children[1]) {
      T->children[1]->llvm_before = T->llvm_before;
      T->children[1]->llvm_after = T->llvm_after;
      gen_all(T->children[1]);
    }
    break;
  
  // Control flow statement section.
  // We need to set new basic blocks and point ther
  // builder to them frequently here.
  case IF_THEN:

    // Evaluate the If-clause and save current basic block.
    gen_expr(T->children[0]);
    bbefore = cur_bblock;

    // Then clause, a new basic block.
    cur_bblock = LLVMAppendBasicBlock(cur_func, new_bblock());
    btrue = cur_bblock;
    LLVMPositionBuilderAtEnd(builder, cur_bblock);
    T->children[1]->llvm_before = T->llvm_before;
    T->children[1]->llvm_after = T->llvm_after;
    gen_all(T->children[1]);

    // After clause, a new basic block.
    cur_bblock = LLVMAppendBasicBlock(cur_func, new_bblock());
    bafter = cur_bblock;
    LLVMPositionBuilderAtEnd(builder, cur_bblock);

    // Build the branch instruction.
    // Remember to switch the position of builder.
    LLVMPositionBuilderAtEnd(builder, bbefore);
    LLVMBuildCondBr(builder, 
      LLVM_CONDITION(T->children[0]->llvm_value), btrue, bafter);
    if (!LLVMGetBasicBlockTerminator(btrue)) {
      LLVMPositionBuilderAtEnd(builder, btrue);
      LLVMBuildBr(builder, bafter);
    }
    LLVMPositionBuilderAtEnd(builder, bafter);

    break;
 
  case IF_THEN_ELSE:
  
    // Evaluate the If-clause and save current basic block.
    gen_expr(T->children[0]);
    bbefore = cur_bblock;

    // Then clause, a new basic block.
    cur_bblock = LLVMAppendBasicBlock(cur_func, new_bblock());
    btrue = cur_bblock;
    LLVMPositionBuilderAtEnd(builder, cur_bblock);
    T->children[1]->llvm_before = T->llvm_before;
    T->children[1]->llvm_after = T->llvm_after;
    gen_all(T->children[1]);

    // Else clause, a new basic block.
    cur_bblock = LLVMAppendBasicBlock(cur_func, new_bblock());
    bfalse = cur_bblock;
    LLVMPositionBuilderAtEnd(builder, cur_bblock);
    T->children[2]->llvm_before = T->llvm_before;
    T->children[2]->llvm_after = T->llvm_after;
    gen_all(T->children[2]);

    // After clause, a new basic block.
    cur_bblock = LLVMAppendBasicBlock(cur_func, new_bblock());
    bafter = cur_bblock;
    LLVMPositionBuilderAtEnd(builder, cur_bblock);

    // Build the condition branch instruction.
    // Remember to switch the position of builder.
    LLVMPositionBuilderAtEnd(builder, bbefore);
    LLVMBuildCondBr(builder, 
      LLVM_CONDITION(T->children[0]->llvm_value), btrue, bfalse);

    // Build the branch instruction at the end of
    // Then-clause and Else-clause.
    if (!LLVMGetBasicBlockTerminator(btrue)) {
      LLVMPositionBuilderAtEnd(builder, btrue);
      LLVMBuildBr(builder, bafter);
    }
    if (!LLVMGetBasicBlockTerminator(bfalse)) {
      LLVMPositionBuilderAtEnd(builder, bfalse);
      LLVMBuildBr(builder, bafter);
    }
    LLVMPositionBuilderAtEnd(builder, bafter);

    break;

  case WHILE:

    // Evaluate the While-clause and create a new
    // basic block here.
    cur_bblock = LLVMAppendBasicBlock(cur_func, new_bblock());
    bbefore = cur_bblock;
    LLVMBuildBr(builder, cur_bblock);
    LLVMPositionBuilderAtEnd(builder, cur_bblock);
    gen_expr(T->children[0]);

    // Pre-allocate the basic block for break and continue.
    cur_bblock = LLVMAppendBasicBlock(cur_func, new_bblock());
    btrue = cur_bblock;
    cur_bblock = LLVMAppendBasicBlock(cur_func, new_bblock());
    bafter = cur_bblock;

    // Build the Loop body.
    LLVMPositionBuilderAtEnd(builder, btrue);
    cur_bblock = btrue;
    T->children[1]->llvm_before = bbefore;
    T->children[1]->llvm_after = bafter;
    gen_all(T->children[1]);

    // Build the branch instruction at the end of
    // While-clause.
    LLVMPositionBuilderAtEnd(builder, bbefore);
    LLVMBuildCondBr(builder, 
      LLVM_CONDITION(T->children[0]->llvm_value), btrue, bafter);

    // Build the branch instruction at the end of loop.
    LLVMPositionBuilderAtEnd(builder, btrue);
    LLVMBuildBr(builder, bbefore);
    LLVMPositionBuilderAtEnd(builder, bafter);
    break;
    
  case FOR:

    // Initialize statement, we don't create new basic
    // blocks here.
    gen_all(T->children[0]);
    
    // Condition clause, like while-clause in while loop.
    cur_bblock = LLVMAppendBasicBlock(cur_func, new_bblock());
    bbefore = cur_bblock;
    LLVMBuildBr(builder, cur_bblock);
    LLVMPositionBuilderAtEnd(builder, cur_bblock);
    gen_expr(T->children[1]);

    // Pre-allocate the basic block for break and continue.
    cur_bblock = LLVMAppendBasicBlock(cur_func, new_bblock());
    btrue = cur_bblock;
    cur_bblock = LLVMAppendBasicBlock(cur_func, new_bblock());
    bafter = cur_bblock;

    // The iterater should be generated after
    // the loop body.
    LLVMPositionBuilderAtEnd(builder, btrue);
    cur_bblock = btrue;
    T->children[3]->llvm_before = bbefore;
    T->children[3]->llvm_after = bafter;
    gen_all(T->children[3]);
    gen_expr(T->children[2]);

    // Build the branch instruction at the end of
    // condition clause.
    LLVMPositionBuilderAtEnd(builder, bbefore);
    LLVMBuildCondBr(builder,
      LLVM_CONDITION(T->children[1]->llvm_value), btrue, bafter);

    // Build the branch instruction at the end of loop.
    LLVMPositionBuilderAtEnd(builder, btrue);
    LLVMBuildBr(builder, bbefore);
    LLVMPositionBuilderAtEnd(builder, bafter);

    break;
    
  case RETURN:
    if (T->children[0]) {
      gen_expr(T->children[0]);
      LLVMBuildRet(builder, T->children[0]->llvm_value);
    } else LLVMBuildRetVoid(builder);
    break;
  
  // Use the nearest bafter and bbefore to implement
  // break and continue.
  case BREAK:
    LLVMBuildBr(builder, T->llvm_after);
  case CONTINUE:
    LLVMBuildBr(builder, T->llvm_before);
  
  case IDENT:
  case L_INT:
  case L_FLOAT:
  case L_CHAR:
  case L_STRING:
	case ASSIGN:
	case COMP_ASSIGN:
	case OP_AND:
	case OP_OR:
  case OP_G:
  case OP_L:
  case OP_GE:
  case OP_LE:
  case OP_EQ:
  case OP_NEQ:
	case OP_ADD:
	case OP_SUB:
	case OP_STAR:
	case OP_DIV:
	case OP_MOD:
	case OP_NOT:
	case OP_INC:
	case OP_DEC:
	case UMINUS:
  case FUNC_CALL:
  case ARRAY_CALL:
  case MEMBER_CALL:
    gen_expr(T);
    break;
  }
}

void generate_IR(ast_node* T, char* input, char* output) {
  module = LLVMModuleCreateWithName(input);
  builder = LLVMCreateBuilder();

  gen_all(T);
  if (output) LLVMPrintModuleToFile(module, output, NULL);

#ifdef SHOW_IR
  LLVMDumpModule(module);
#endif
  LLVMDisposeModule(module);
}