
#include <lib/ast.h>
#include <lib/semantic.h>

// The symbol table.
symbol_table stab;

static int sem_check_var_list(ast_node* T);
static int sem_check_arg(st_index symbol, ast_node* T);
static int sem_check_struct(ast_node* T);
static int sem_check_expr(ast_node* T);
static int sem_check(ast_node* T);

// Allocate and return a new variable alias.
static char* new_alias() {
  static int cnt = 0;
  static char alias[MAX_ALIAS_LEN] = {0};
  sprintf(alias, "G%d", cnt);
  cnt++;
  return alias;
}

// Allocate and return a new temp alias.
static char* new_tmp() {
  static int cnt = 0;
  static char tmp[MAX_ALIAS_LEN] = {0};
  sprintf(tmp, "T%d", cnt);
  cnt++;
  return tmp;
}

// Display the symbol table.
void stab_display() {
  PRINT_BORDER();
  printf("| %s | %-18s | %-5s | %s | %-6s | %-9s |\n",
    "ID", "Name", "Alias", "Scope", "DType", "SType"
  );
  PRINT_BORDER();

  for (int i = 0; i < LEN(stab.stack); i++) {
    for (int j = 0; j < SCOPE(i).size; j++) {
      st_index index = ST_INDEX(i, j);
      char* dots = (strlen(SYMBOL(index).name) > 15) ?
        "..." : "   ";

      printf("| %-2d | %-15.15s%s | %-5s | %-5d | %-6s | %-9s |\n",
        j,
        SYMBOL(index).name,
        dots,
        SYMBOL(index).alias,
        NTH(stab.stack, i),
        ast_table[SYMBOL(index).dtype],
        symbol_name[SYMBOL(index).stype]
      );
    }
  }

  PRINT_BORDER();
}

// Search from the symbol table to find target symbol.
st_index stab_search(char *name) {
  int flag = 0;

  // Search from the latest scope to the global scope.
  for (int i = CUR_SCOPE; i >= 0; i--) {
    for (int j = 0; j < SCOPE(i).size; j++) {

      // Return the index of symbol if matched.
      if (!strcmp(SYMBOL(ST_INDEX(i, j)).name, name))
        return ST_INDEX(i, j);
    }
  }

  // If there's no match, return an error.
  return -ENOSYMBOL;
}

// Add a symbol to the symbol table.
st_index stab_add(char *name, char *alias, int scope, int dtype, char stype) {
  st_index index = ST_INDEX(scope, SCOPE(scope).size);

  // Search in the same scope scope for a duplicated
  // symbol.
  for (int i = 0; i < SCOPE(scope).size; i++) {

    // If there exists an symbol with the same name as
    // the symbol to be added, return an error.
    if (!strcmp(SYMBOL(ST_INDEX(scope, i)).name, name))
      return -EDUPSYMBOL;
  }

  // Fill the symbol table entry.
  strcpy(SYMBOL(index).name, name);
  strcpy(SYMBOL(index).alias, alias);
  SYMBOL(index).dtype = dtype;
  SYMBOL(index).stype = stype;

  // Return the index of the inserted symbol.
  SCOPE(scope).size++;
  return index;
}

// Add a temporary symbol to the symbol table.
st_index stab_add_tmp(char *alias, int level, int dtype, char stype) {
  st_index index = ST_INDEX(level, SCOPE(level).size);

  // Fill the symbol table entry.
  strcpy(SYMBOL(index).name, "-");
  strcpy(SYMBOL(index).alias, alias);
  SYMBOL(index).dtype = dtype;
  SYMBOL(index).stype = stype;

  // Return the index of the inserted symbol.
  SCOPE(level).size++;
  return ST_INDEX(level, SCOPE(level).size-1);
}

// Semantic check: variable list.
static int sem_check_var_list(ast_node* T) {
  st_index sym;
  int err = 0;

  switch (T->type) {
  case EXT_DECL_LIST:
  case DEC_LIST:

    // Pass the type and offset information downward.
    T->children[0]->dtype = T->children[1]->dtype = T->dtype;
    T->children[0]->parent_struct = 
    T->children[1]->parent_struct = T->parent_struct;
    T->children[0]->symbol = 
    T->children[1]->symbol = T->symbol;
    err |= sem_check_var_list(T->children[0]);
    err |= sem_check_var_list(T->children[1]);

    // Count the number of variables in recursion.
    T->num = T->children[1]->num + 1;
    break;

  // Record the variable in the symbol table.
  case IDENT:
    sym = stab_add(T->value.str, new_alias(), CUR_SCOPE,
      T->dtype, VAR);
    if (sym == -EDUPSYMBOL) {
      fault(-EDUPSYMBOL, T->lineno, T->value.str);
      err = 1;
    } else {

      // If this variable is a struct member
      // or a struct variable
      if (T->symbol) {
        SYMBOL(sym).struct_type = T->symbol;
      }
      if (T->parent_struct) {
        SYMBOL(sym).parent_struct = T->parent_struct;
      }
      T->symbol = sym;
    }
    T->num = 1;

    // Is this identifier an array?
    SYMBOL(sym).dim = T->dim;
    for (int i = 0; i < T->dim; i++)
      SYMBOL(sym).capacity[i] = T->capacity[i];
    break;
  
  case VAR_INIT:
    T->children[0]->dtype = T->dtype;
    err |= sem_check_var_list(T->children[0]);
    err |= sem_check_expr(T->children[1]);

    // Check the type of initializer.
    if (T->dtype != T->children[1]->dtype || 
    SYMBOL(T->children[0]->symbol).dim) {
      fault(-EWRONGINITTYPE, T->lineno,
        ast_table[T->children[1]->dtype], T->children[0]->value.str);
      err = 1;
    }

    T->num = T->children[1]->num;
    break;
  }
  
  return err;
}

// Semantic check: arguments of a function call.
static int sem_check_arg(st_index symbol, ast_node* T) {
  int ideal_num = SYMBOL(symbol).param_num;
  int param_scope = SYMBOL(symbol).param_scope;
  int err_pos = T->lineno;
  char* func_name = T->value.str;
  int err = 0;

  // If this function does not have parameters:
  T = T->children[0];
  if (!ideal_num && !T) return err;

  // Try to match each parameter with an argument.
  for (int i = 0; i < ideal_num; i++) {

    // Lack of arguments.
    if (!T) {
      fault(-ELACKARG, err_pos, func_name, ideal_num, i);
      err = 1;
      break;
    }

    // Wrong type of argument.
    err |= sem_check_expr(T->children[0]);
    if (SYMBOL_GLOB(param_scope, i).dtype != T->children[0]->dtype) {
      fault(-EWRONGARGTYPE, err_pos, i + 1, func_name,
        ast_table[SYMBOL_GLOB(param_scope, i).dtype],
        ast_table[T->children[0]->dtype]);
      err = 1;
    }

    T = T->children[1];
  }

  // Too many arguments.
  if (T) {
    fault(-EEXTRAARG, err_pos, func_name, ideal_num);
    err = 1;
  }

  return err;
}

// Semantic check: struct variable declaration.
static int sem_check_struct(ast_node* T) {
  st_index sym;
  int err = 0;

  // Define a struct and declear corresponding
  // variables right away.
  if (T->children[0]) {
    sym = stab_add(T->value.str, new_alias(), CUR_SCOPE,
      T_STRUCT, STRUCT);
    if (sym == -EDUPSYMBOL) {
      fault(-EDUPSYMBOL, T->lineno, T->value.str);
      return err;
    }

    T->symbol = sym;
    T->children[0]->parent_struct = sym;
    err |= sem_check(T->children[0]);

  // Use a pre-defined struct.
  } else {
    sym = stab_search(T->value.str);
    if (sym == -ENOSYMBOL) {
      fault(-ENOSYMBOL, T->lineno, T->value.str);
      return err;
    }

    T->symbol = sym;
  }
  
  return err;
}

// Semantic check: expressions.
static int sem_check_expr(ast_node* T) {
  st_index sym;
  int type, type_ext;
  int err = 0;

  if (T) switch (T->type) {
  case IDENT:
    sym = stab_search(T->value.str);

    // Variable not defined.
    if (sym == -ENOSYMBOL) {
      fault(-ENOSYMBOL, T->lineno, T->value.str);
      err = 1;
      break;
    }
    
    // Function name.
    if (SYMBOL(sym).stype == FUNC) {
      fault(-EFUNCASVAR, T->lineno, T->value.str);
      err = 1;
    } else {
      T->symbol = sym;
      T->dtype = SYMBOL(sym).dtype;
    }
    break;

  case L_INT:
    T->dtype = T_INT;
    break;
  case L_CHAR:
    T->dtype = T_CHAR;
    break;
  case L_FLOAT:
    T->dtype = T_FLOAT;
    break;
  case L_STRING:
    T->dtype = T_STRING;
    break;

  // Assigning.
  case ASSIGN:
  case COMP_ASSIGN:
    err |= sem_check_expr(T->children[0]);
    err |= sem_check_expr(T->children[1]);
    T->dtype = T->children[0]->dtype;

    // Type conflict
    if (T->children[0]->dtype != T->children[1]->dtype ||
    T->children[0]->dim) {
      fault(-EDIFFOPETYPE, T->lineno, "assignment");
      err = 1;
    }

    if (T->type == COMP_ASSIGN)
      T->symbol = stab_add_tmp(new_tmp(), CUR_SCOPE, T->dtype, TEMP);
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
    err |= sem_check_expr(T->children[0]);
    err |= sem_check_expr(T->children[1]);
    T->dtype = T_INT;

    T->symbol = stab_add_tmp(new_tmp(), CUR_SCOPE, T->dtype, TEMP);
    break;

  // Arithmetic expressions.
  case OP_ADD:
  case OP_SUB:
  case OP_STAR:
  case OP_DIV:
    err |= sem_check_expr(T->children[0]);
    err |= sem_check_expr(T->children[1]);
    type = T->children[0]->dtype;
    type_ext = T->children[1]->dtype;

    // Some data types does not support such operations.
    if (type == T_STRING || type_ext == T_STRING) {
      fault(-EWRONGOPETYPE, T->lineno, ast_table[T->type], "strings");
      err = 1;
    } else if (type == T_STRUCT || type_ext == T_STRUCT) {
      fault(-EWRONGOPETYPE, T->lineno, ast_table[T->type], "structs");
      err = 1;
    } else if (SYMBOL(T->children[0]->symbol).dim ||
        SYMBOL(T->children[1]->symbol).dim) {
      fault(-EWRONGOPETYPE, T->lineno, ast_table[T->type], "arrays");
      err = 1;
    }

    // We support a little bit of implicit type conversion here.
    if (type == T_FLOAT || type_ext == T_FLOAT) {
      T->dtype = T_FLOAT;
    } else {
      T->dtype = T_INT;
    }

    T->symbol = stab_add_tmp(new_tmp(), CUR_SCOPE, T->dtype, TEMP);
    break;

  case OP_MOD:
    err |= sem_check_expr(T->children[0]);
    err |= sem_check_expr(T->children[1]);

    // Operands must have the same data type.
    if (T->children[0]->dtype != T->children[0]->dtype) {
      fault(-EDIFFOPETYPE, T->lineno, ast_table[T->type]);
      err = 1;
    }

    // Some data types does not support such operations.
    if (T->children[0]->dtype != T_INT) {
      fault(-EWRONGOPETYPE, T->lineno,
        ast_table[T->type], ast_table[T->children[0]->dtype]);
      err = 1;
    }

    T->dtype = T_INT;
    T->symbol = stab_add_tmp(new_tmp(), CUR_SCOPE, T->dtype, TEMP);
    break;

  // Single-operand expressions.
  case OP_DEC:
  case OP_INC:
  case OP_NOT:
  case UMINUS:
    err |= sem_check_expr(T->children[0]);

    // Some data types does not support such operations.
    if (T->children[0]->dtype == T_INT) {
      T->dtype = T_INT;
    } else if (T->children[0]->dtype == T_FLOAT) {
      T->dtype = T_FLOAT;
    } else if (T->children[0]->dtype == T_CHAR) {
      T->dtype = T_CHAR;
    } else {
      fault(-EWRONGOPETYPE, T->lineno,
        ast_table[T->type], ast_table[T->children[0]->dtype]);
      T->dtype = T_INT;
      err = 1;
    }

    T->symbol = stab_add_tmp(new_tmp(), CUR_SCOPE, T->dtype, TEMP);
    break;

  // Dot operator has strict requirements.
  case MEMBER_CALL:
    err |= sem_check_expr(T->children[0]);

    // Left operand is not a struct.
    if (T->children[0]->dtype != T_STRUCT) {
      fault(-ENOTSTRUCT, T->lineno, 
        SYMBOL(T->children[0]->symbol).name);
      err = 1;
      break;
    }

    // Member not defined.
    sym = stab_search(T->value.str);
    if (sym == -ENOSYMBOL) {
      fault(-ENOSYMBOL, T->lineno, T->value.str);
      err = 1;
      break;
    }

    // Not the member of this struct.
    if (SYMBOL(sym).parent_struct != 
      SYMBOL(T->children[0]->symbol).struct_type) {
      fault(-ENOTMEMBER, T->lineno,
        SYMBOL(sym).name,
        SYMBOL(T->children[0]->symbol).name
      );
      err = 1;
    }

    T->dtype = SYMBOL(sym).dtype;
    T->symbol = sym;

    // T->symbol is occupied by the symbol of member
    // so we need to leverage T->parent_struct to store
    // the value of member call here.
    T->parent_struct = stab_add_tmp(new_tmp(), CUR_SCOPE, T->dtype, TEMP);
    break;

  case FUNC_CALL:

    // Do not check inline function calls.
    if (!strcmp(T->value.str, "printf")) break;
   
    sym = stab_search(T->value.str);

    // Function not defined.
    if (sym == -ENOSYMBOL) {
      fault(-ENOSYMBOL, T->lineno, T->value.str);
      err = 1;
      break;
    }
    
    // Not a function.
    if (SYMBOL(sym).stype != FUNC) {
      fault(-ENOTFUNC, T->lineno, T->value.str);
      err = 1;
      break;
    }
    T->dtype = SYMBOL(sym).dtype;

    // Evaluate all arguments.
    if (T->children[0]) {
      err |= sem_check_expr(T->children[0]);
    }
    err |= sem_check_arg(sym, T);

    T->symbol = stab_add_tmp(new_tmp(), CUR_SCOPE, T->dtype, TEMP);
    break;

  case ARG_LIST:
    err |= sem_check_expr(T->children[0]);

    if (T->children[1]) {
      err |= sem_check_expr(T->children[1]);
    }
    break;
  
  case ARRAY_CALL:
    err |= sem_check_expr(T->children[0]);
    err |= sem_check_expr(T->children[1]);

    // Identifier is not an array variable.
    if (!SYMBOL(T->children[0]->symbol).dim) {
      fault(-ENOTARRAY, T->lineno, T->children[0]->value.str);
      err = 1;
    }

    // Subscript is not an integer.
    if (T->children[1]->dtype != T_INT) {
      fault(-EWRONGSUBSCRIPTTYPE, T->lineno);
      err = 1;
    }

    T->dtype = T->children[0]->dtype;
    T->symbol = stab_add_tmp(new_tmp(), CUR_SCOPE, T->dtype, TEMP);

    SYMBOL(T->symbol).dim = SYMBOL(T->children[0]->symbol).dim - 1;
    for (int i = 0; i < SYMBOL(T->symbol).dim; i++)
      SYMBOL(T->symbol).capacity[i] = 
      SYMBOL(T->children[0]->symbol).capacity[i];
    break;
  }

  return err;
}

static int sem_check(ast_node* T) {
  st_index sym;
  int err = 0;

  if (T) switch (T->type) {
  case EXT_DEF_LIST:
    if (T->children[0]) {
      err |= sem_check(T->children[0]);
      if (T->children[1]) {
        err |= sem_check(T->children[1]);
      }
    }
    break;

  case EXT_VAR_DEF:
  case VAR_DEF:
    if (T->children[0]->type == T_STRUCT) {
      sem_check_struct(T->children[0]);
      T->children[1]->symbol = T->children[0]->symbol;
    }
    
    T->dtype = T->children[1]->dtype = T->children[0]->type;
    err |= sem_check_var_list(T->children[1]);
    break;
  
  case STRUCT_DEF:
    sym = stab_add(T->value.str, new_alias(), CUR_SCOPE,
      T_STRUCT, STRUCT);
    if (sym == -EDUPSYMBOL) {
      fault(-EDUPSYMBOL, T->lineno, T->value.str);
      err = 1;
      break;
    }

    T->symbol = sym;
    if (T->children[0]) {
      T->children[0]->parent_struct = sym;
      err |= sem_check(T->children[0]);
    } 
    break;

  case MEMBER_LIST:
    if (T->children[0]->type == T_STRUCT) {
      sem_check_struct(T->children[0]);
      T->children[1]->symbol = T->children[0]->symbol;
    }

    T->dtype = T->children[1]->dtype = T->children[0]->type;
    T->children[1]->parent_struct = T->parent_struct;
    err |= sem_check_var_list(T->children[1]);
    if (T->children[2]) {
      T->children[2]->parent_struct = T->parent_struct;
      err |= sem_check(T->children[2]);
    }
    break;
  
  case FUNC_DEF:
    T->children[1]->dtype = T->children[0]->type;
    err |= sem_check(T->children[1]);

    T->children[2]->symbol = T->children[1]->symbol;
    err |= sem_check(T->children[2]);
    SCOPE_POP();
    
    // Is this function returned?
    if (SYMBOL(T->children[1]->symbol).dtype != T_VOID &&
      !SYMBOL(T->children[1]->symbol).returned) {
        fault(-ENOTRETURNED, T->lineno,
        SYMBOL(T->children[1]->symbol).name);
      err = 1;
    }
    break;

  case FUNC_DECL:
    sym = stab_add(T->value.str, new_alias(), CUR_SCOPE,
      T->dtype, FUNC);
    if (sym == -EDUPSYMBOL) {
      fault(-EDUPSYMBOL, T->lineno, T->value.str);
      err = 1;
      break;
    }

    T->symbol = sym;
    SCOPE_PUSH();
    SYMBOL(sym).param_scope = NTH(stab.stack, CUR_SCOPE);
    if (T->children[0]) {
      err |= sem_check(T->children[0]);
      SYMBOL(sym).param_num = T->children[0]->num;
    }
    break;
  
  case PARAM_LIST:
    err |= sem_check(T->children[0]);
    if (T->children[1]) {
      err |= sem_check(T->children[1]);
      T->num = T->children[0]->num + T->children[1]->num;
    } else {
      T->num = T->children[0]->num;
    }
    break;
  
  case PARAM_DEC:
    if (T->children[0]->type == T_STRUCT) {
      sem_check_struct(T->children[0]);
    }
    
    sym = stab_add(T->children[1]->value.str, new_alias(),
      1, T->children[0]->type, PARAM);
    if (sym == -EDUPSYMBOL) {
      fault(-EDUPSYMBOL, T->lineno, T->value.str);
      err = 1;
    } else {
      // If this param is a struct variable
      if (T->children[0]->symbol) {
        SYMBOL(sym).struct_type = T->children[0]->symbol;
      }
    }
    
    T->children[1]->symbol = sym;
    T->num = 1;
    break;

  case CODE_BLOCK:
    SCOPE_PUSH();
    if (T->children[0]) {
      T->children[0]->symbol = T->symbol;
      T->children[0]->looping = T->looping;
    }
    err |= sem_check(T->children[0]);

    SCOPE_POP();
    break;
  
  case STMT_LIST:
    if (T->children[0]) {
      T->children[0]->symbol = T->symbol;
      T->children[0]->looping = T->looping;
      err |= sem_check(T->children[0]);
    }
    if (T->children[1]) {
      T->children[1]->symbol = T->symbol;
      T->children[1]->looping = T->looping;
      err |= sem_check(T->children[1]);
    }
    break;
  
  case IF_THEN:
    err |= sem_check_expr(T->children[0]);
    T->children[1]->symbol = T->symbol;
    T->children[1]->looping = T->looping;
    err |= sem_check(T->children[1]);
    break;
 
  case IF_THEN_ELSE:
    err |= sem_check_expr(T->children[0]);
    T->children[1]->symbol = T->symbol;
    T->children[1]->looping = T->looping;
    err |= sem_check(T->children[1]);
    T->children[2]->symbol = T->symbol;
    T->children[2]->looping = T->looping;
    err |= sem_check(T->children[2]);
    break;

  case WHILE:
    err |= sem_check_expr(T->children[0]);
    T->children[1]->symbol = T->symbol;
    T->children[1]->looping = 1;
    err |= sem_check(T->children[1]);
    break;
    
  case FOR:
    SCOPE_PUSH();
    T->children[0]->symbol = T->symbol;
    T->children[0]->looping = T->looping;
    err |= sem_check(T->children[0]);
    err |= sem_check_expr(T->children[1]);
    err |= sem_check_expr(T->children[2]);
    T->children[3]->symbol = T->symbol;
    T->children[3]->looping = 1;
    err |= sem_check(T->children[3]);
    SCOPE_POP();
    break;
    
  case RETURN:
    if (T->children[0]) {
      err |= sem_check_expr(T->children[0]);

      // Check return type
      if (T->children[0]->dtype != SYMBOL(T->symbol).dtype) {
        fault(-EWRONGRETTYPE, T->lineno, ast_table[T->children[0]->dtype],
          ast_table[SYMBOL(T->symbol).dtype]);
        err = 1;
      }

    // Check return type void
    } else {
      if (SYMBOL(T->symbol).dtype != T_VOID) {
        fault(-EWRONGRETTYPE, T->lineno,
          "void", ast_table[SYMBOL(T->symbol).dtype]);
        err = 1;
      }
    }

    SYMBOL(T->symbol).returned = 1;
    break;
  
  case BREAK:
  case CONTINUE:
    if (!T->looping) {
      fault(-ENOTINLOOP, T->lineno, ast_table[T->type]);
      err = 1;
    }
  
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
    err |= sem_check_expr(T);
    break;
  }

  return err;
}

// Do the semantic analysis.
void semantic_analysis(ast_node* T) {

  // Initialize the symbol table.
  stab.scopes = LIST_NEW(scope_list, symbol_scope);
  stab.stack = LIST_NEW(index_list, int);

  // Initialize the symbol scope.
  // Symbol 0 in the global scope should be empty
  // because its st_index is 0, which represents
  // no symbol.
  SCOPE_PUSH();
  stab_add("-", "-", CUR_SCOPE, T_INT, VAR);

  // Initialize the pre-defined symbols.
  st_index index = stab_add(
    "printf", "P1", CUR_SCOPE, T_INT, FUNC);
  SYMBOL(index).param_num = 1;

  // Do the semantic analysis
  if (sem_check(T)) {
    exit(1);
  }
}