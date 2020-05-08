
#include <lib/ast.h>
#include <lib/semantic.h>

// The symbol table.
symbol_table stab;

// Current level.
static int cur_level;

static int sem_check_var_list(ast_node* T);
static int sem_check_arg(int symbol, ast_node* T);
static int sem_check_struct(ast_node* T);
static int sem_check_expr(ast_node* T);
static int sem_check(ast_node* T);

static char* new_alias() {
  static int cnt = 0;
  static char alias[MAX_ALIAS_LEN] = {0};
  sprintf(alias, ".L%d", cnt);
  cnt++;
  return alias;
}

static char* new_tmp() {
  static int cnt = 0;
  static char tmp[MAX_ALIAS_LEN] = {0};
  sprintf(tmp, ".T%d", cnt);
  cnt++;
  return tmp;
}

// Display the symbol table.
void stab_display() {
  PRINT_BORDER();
  printf("| %s | %-13s | %-5s | %s | %-6s | %-9s | %s |\n",
    "ID", "Name", "Alias", "Level", "DType", "SType", "Offset"
  );
  PRINT_BORDER();

  for (int i = 0; i < stab.size; i++) {
    char* dots = (strlen(stab.symbols[i].name) > 10) ?
      "..." : "   ";
    printf("| %-2d | %-10.10s%s | %-5s | %-5d | %-6s | %-9s | %-6d |\n",
      i,
      stab.symbols[i].name,
      dots,
      stab.symbols[i].alias,
      stab.symbols[i].level,
      ast_table[stab.symbols[i].dtype],
      symbol_name[stab.symbols[i].stype],
      stab.symbols[i].offset
    );
  }

  PRINT_BORDER();
}

// Search from the symbol table to find target symbol.
int stab_search(char *name) {
  int flag = 0;
  for(int i = stab.size-1; i >= 0; i--){

    // Skip parameters of the function.
    if (stab.symbols[i].level == 0) flag = 1;
    if (flag && stab.symbols[i].level == 1) continue;

    // Return the index of symbol if matched.
    if (!strcmp(stab.symbols[i].name, name))
      return i;
  }

  // If there's no match, return an error.
  return -ENOSYMBOL;
}

// Add a symbol to the symbol table.
int stab_add(char *name, char *alias, int level, int dtype, char stype, int offset) {

  // Search in the same scope level for a duplicated
  // symbol.
  for (int i = stab.size-1; i >= 0 &&
    (stab.symbols[i].level == level || level == 0); i--) {

    // We allow external variables to have the same name
    // with function parameters.
    if (level == 0 && stab.symbols[i].level == 1) continue;

    // If there exists an symbol with the same name as
    // the symbol to be added, return an error.
    if (!strcmp(stab.symbols[i].name, name))
      return -EDUPSYMBOL;
  }

  // Fill the symbol table entry.
  strcpy(stab.symbols[stab.size].name, name);
  strcpy(stab.symbols[stab.size].alias, alias);
  stab.symbols[stab.size].level = level;
  stab.symbols[stab.size].dtype = dtype;
  stab.symbols[stab.size].stype = stype;
  stab.symbols[stab.size].offset = offset;

  // Return the index of the inserted symbol.
  stab.size++;
  return stab.size-1;
}

// Add a temporary symbol to the symbol table.
int stab_add_tmp(char *alias, int level, int dtype, char stype, int offset) {

  // Fill the symbol table entry.
  strcpy(stab.symbols[stab.size].name, "-");
  strcpy(stab.symbols[stab.size].alias, alias);
  stab.symbols[stab.size].level = level;
  stab.symbols[stab.size].dtype = dtype;
  stab.symbols[stab.size].stype = stype;
  stab.symbols[stab.size].offset = offset;

  // Return the index of the inserted symbol.
  stab.size++;
  return stab.size-1;
}

// Semantic check: variable list.
static int sem_check_var_list(ast_node* T) {
  int sym;
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
    T->children[0]->offset = T->offset;
    T->children[1]->offset = T->offset + T->width;
    T->children[1]->width = T->width;
    err |= sem_check_var_list(T->children[0]);
    err |= sem_check_var_list(T->children[1]);

    // Count the number of variables in recursion.
    T->num = T->children[1]->num + 1;
    break;

  // Record the variable in the symbol table.
  case IDENT:
    sym = stab_add(T->value.str, new_alias(), cur_level,
      T->dtype, VAR, T->offset);
    if (sym == -EDUPSYMBOL) {
      fault(-EDUPSYMBOL, T->lineno, T->value.str);
      err = 1;
    } else {
      // If this variable is a struct member
      // or a struct variable
      if (T->symbol) {
        stab.symbols[sym].struct_type = T->symbol;
      }
      if (T->parent_struct) {
        stab.symbols[sym].parent_struct = T->parent_struct;
      }
      T->symbol = sym;
    }
    T->num = 1;

    // Is this identifier an array?
    if (T->dim > 0) stab.symbols[sym].isarray = 1;
    break;
  
  case VAR_INIT:
    T->children[0]->dtype = T->dtype;
    T->children[0]->offset = T->offset;
    T->children[1]->offset = T->offset + T->width;
    T->children[1]->width = T->width;
    err |= sem_check_var_list(T->children[0]);
    err |= sem_check_expr(T->children[1]);

    // Check the type of initializer.
    if (T->dtype != T->children[1]->dtype || 
    stab.symbols[T->children[0]->symbol].isarray) {
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
static int sem_check_arg(int symbol, ast_node* T) {
  int ideal_num = stab.symbols[symbol].param_num;
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
    T->children[0]->offset = T->offset;
    err |= sem_check_expr(T->children[0]);
    if (stab.symbols[symbol+i].dtype != T->children[0]->dtype) {
      fault(-EWRONGARGTYPE, err_pos,
        i + 1, func_name,
        ast_table[stab.symbols[symbol+i].dtype],
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
  int sym, err = 0;

  // Define a struct and declear corresponding
  // variables right away.
  if (T->children[0]) {
    sym = stab_add(T->value.str, new_alias(), cur_level,
      T_STRUCT, STRUCT, T->offset);
    if (sym == -EDUPSYMBOL) {
      fault(-EDUPSYMBOL, T->lineno, T->value.str);
      return err;
    }

    T->symbol = sym;
    T->children[0]->parent_struct = sym;
    T->children[0]->offset = T->offset;
    err |= sem_check(T->children[0]);
    T->width = T->children[0]->width;

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
  int sym;
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
    if (stab.symbols[sym].stype == FUNC) {
      fault(-EFUNCASVAR, T->lineno, T->value.str);
      err = 1;
    } else {
      T->symbol = sym;
      T->dtype = stab.symbols[sym].dtype;
      T->offset = stab.symbols[sym].offset;
      T->width = 0;
    }
    break;

  case L_INT:
    T->symbol = stab_add_tmp(new_tmp(), cur_level,
      T_INT, TEMP, T->offset);
    T->dtype = T_INT;
    T->width = 4;
    break;
  case L_CHAR:
    T->symbol = stab_add_tmp(new_tmp(), cur_level,
      T_CHAR, TEMP, T->offset);
    T->dtype = T_CHAR;
    T->width = 1;
    break;
  case L_FLOAT:
    T->symbol = stab_add_tmp(new_tmp(), cur_level,
      T_FLOAT, TEMP, T->offset);
    T->dtype = T_FLOAT;
    T->width = 4;
    break;
  case L_STRING:
    T->symbol = stab_add_tmp(new_tmp(), cur_level,
      T_STRING, TEMP, T->offset);
    T->dtype = T_STRING;
    T->width = sizeof(char *);
    break;

  case ASSIGN:
  case COMP_ASSIGN:
    err |= sem_check_expr(T->children[0]);
    T->children[1]->offset = T->offset;
    err |= sem_check_expr(T->children[1]);
    T->dtype = T->children[0]->dtype;
    T->width = T->children[1]->width;

    // Type conflict
    if (T->children[0]->dtype != T->children[1]->dtype) {
      fault(-EDIFFOPETYPE, T->lineno, "assignment");
      err = 1;
    }
    break;

  case OP_AND:
  case OP_OR:
  case OP_G:
  case OP_L:
  case OP_GE:
  case OP_LE:
  case OP_EQ:
  case OP_NEQ:
    T->children[0]->offset = T->children[1]->offset = T->offset;
    err |= sem_check_expr(T->children[0]);
    T->width = T->children[0]->width;
    err |= sem_check_expr(T->children[1]);
    if (T->width < T->children[1]->width)
      T->width = T->children[1]->width;
    T->dtype = T_INT;
    break;

  case OP_ADD:
  case OP_SUB:
  case OP_STAR:
  case OP_DIV:
    T->children[0]->offset = T->offset;
    err |= sem_check_expr(T->children[0]);
    T->children[1]->offset = T->offset + T->children[0]->width;
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
    } else if (stab.symbols[T->children[0]->symbol].isarray ||
        stab.symbols[T->children[1]->symbol].isarray) {
      fault(-EWRONGOPETYPE, T->lineno, ast_table[T->type], "arrays");
      err = 1;
    }

    if (type == T_FLOAT || type_ext == T_FLOAT) {
      T->dtype = T_FLOAT;
      T->width = T->children[0]->width + T->children[1]->width + 4;
    } else {
      T->dtype = T_INT;
      T->width = T->children[0]->width + T->children[1]->width + 2;
    }

    T->symbol = stab_add_tmp(new_tmp(), cur_level, T->dtype, TEMP,
      T->offset + T->children[0]->width + T->children[1]->width);
    break;

  case OP_MOD:
    T->children[0]->offset = T->offset;
    err |= sem_check_expr(T->children[0]);
    T->children[1]->offset = T->offset + T->children[0]->width;
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

    T->width = T->children[0]->width + T->children[1]->width + 2;
    T->dtype = T_INT;
    T->symbol = stab_add_tmp(new_tmp(), cur_level, T->dtype, TEMP,
      T->offset + T->children[0]->width + T->children[1]->width);
    break;
  case OP_DEC:
  case OP_INC:
  case OP_NOT:
  case UMINUS:
    T->children[0]->offset = T->offset;
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

    T->width = T->children[0]->width;
    T->symbol = stab_add_tmp(new_tmp(), cur_level, T->dtype, TEMP,
      T->offset + T->children[0]->width);
    break;

  case MEMBER_CALL:
    T->children[0]->offset = T->offset;
    err |= sem_check_expr(T->children[0]);

    // Dot operator has strict requirements.
    if (T->children[0]->dtype != T_STRUCT) {
      fault(-ENOTSTRUCT, T->lineno, 
        stab.symbols[T->children[0]->symbol].name);
      err = 1;
      break;
    }
    sym = stab_search(T->value.str);
    if (sym == -ENOSYMBOL) {
      fault(-ENOSYMBOL, T->lineno, T->value.str);
      err = 1;
      break;
    }
    if (stab.symbols[sym].parent_struct != 
      stab.symbols[T->children[0]->symbol].struct_type) {
      fault(-ENOTMEMBER, T->lineno,
        stab.symbols[sym].name,
        stab.symbols[T->children[0]->symbol].name
      );
      err = 1;
    }

    T->dtype = stab.symbols[sym].dtype;
    T->symbol = sym;
    break;

  case FUNC_CALL:
    sym = stab_search(T->value.str);

    // Function not defined.
    if (sym == -ENOSYMBOL) {
      fault(-ENOSYMBOL, T->lineno, T->value.str);
      err = 1;
      break;
    }
    
    // Not a function.
    if (stab.symbols[sym].stype != FUNC) {
      fault(-ENOTFUNC, T->lineno, T->value.str);
      err = 1;
      break;
    }
    T->dtype = stab.symbols[sym].dtype;

    // Define the width of return value.
    T->width = WIDTH(T->dtype);

    // Evaluate all arguments.
    if (T->children[0]) {
      T->children[0]->offset = T->offset;
      err |= sem_check_expr(T->children[0]);
      T->width += T->children[0]->width;
    }
    err |= sem_check_arg(sym, T);

    T->symbol = stab_add_tmp(new_tmp(), cur_level, T->dtype, TEMP,
      T->offset + (T->children[0] ? T->children[0]->width : 0));
    break;

  case ARG_LIST:
    T->children[0]->offset = T->offset;
    err |= sem_check_expr(T->children[0]);
    T->width = T->children[0]->width;

    if (T->children[1]) {
      T->children[1]->offset = T->offset + T->children[0]->width;
      err |= sem_check_expr(T->children[1]);
      T->width += T->children[1]->width;
    }
    break;
  
  case ARRAY_CALL:
    T->children[0]->offset = T->offset;
    err |= sem_check_expr(T->children[0]);
    T->symbol = T->children[0]->symbol;
    T->children[1]->offset = T->offset + T->children[0]->width;
    err |= sem_check_expr(T->children[1]);

    // Identifier is not an array variable.
    if (!stab.symbols[T->symbol].isarray) {
      fault(-ENOTARRAY, T->lineno, T->children[0]->value.str);
      err = 1;
    }

    // Subscript is not an integer.
    if (T->children[1]->dtype != T_INT) {
      fault(-EWRONGSUBSCRIPTTYPE, T->lineno);
      err = 1;
    }

    T->dtype = T->children[0]->dtype;
    break;
  }

  return err;
}

static int sem_check(ast_node* T) {
  int sym;
  int err = 0;

  if (T) switch (T->type) {
  case EXT_DEF_LIST:
    if (T->children[0]) {
      T->children[0]->offset = T->offset;
      err |= sem_check(T->children[0]);
      if (T->children[1]) {
        T->children[1]->offset = T->offset + T->children[0]->width;
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
    T->children[1]->offset = T->offset;
    T->children[1]->width = WIDTH(T->dtype);
    err |= sem_check_var_list(T->children[1]);
    T->width = WIDTH(T->dtype) * T->children[1]->num;
    break;
  
  case STRUCT_DEF:
    sym = stab_add(T->value.str, new_alias(), cur_level,
      T_STRUCT, STRUCT, BASE_OFFSET);
    if (sym == -EDUPSYMBOL) {
      fault(-EDUPSYMBOL, T->lineno, T->value.str);
      err = 1;
      break;
    }

    T->symbol = sym;
    T->offset = BASE_OFFSET;
    if (T->children[0]) {
      T->children[0]->parent_struct = sym;
      T->children[0]->offset = T->offset;
      err |= sem_check(T->children[0]);
      T->width = T->children[0]->width;
    } 
    break;

  case MEMBER_LIST:
    if (T->children[0]->type == T_STRUCT) {
      sem_check_struct(T->children[0]);
      T->children[1]->symbol = T->children[0]->symbol;
    }

    T->dtype = T->children[1]->dtype = T->children[0]->type;
    T->children[1]->offset = T->offset;
    T->children[1]->width = WIDTH(T->dtype);
    T->children[1]->parent_struct = T->parent_struct;
    err |= sem_check_var_list(T->children[1]);
    T->width = WIDTH(T->dtype) * T->children[1]->num;
    if (T->children[2]) {
      T->children[2]->parent_struct = T->parent_struct;
      T->children[2]->offset = T->offset + T->children[0]->width;
      err |= sem_check(T->children[2]);
    }
    break;
  
  case FUNC_DEF:
    T->children[1]->dtype = T->children[0]->type;
    T->width = 0;
    T->offset = BASE_OFFSET;
    err |= sem_check(T->children[1]);
    T->offset += T->children[1]->width;
    T->children[2]->offset += T->offset;
    T->children[2]->symbol = T->children[1]->symbol;
    err |= sem_check(T->children[2]);
    stab.symbols[T->children[1]->symbol].offset =
      T->offset + T->children[2]->width;
    
    // Is this function returned?
    if (stab.symbols[T->children[1]->symbol].dtype != T_VOID &&
      !stab.symbols[T->children[1]->symbol].returned) {
        fault(-ENOTRETURNED, T->lineno,
        stab.symbols[T->children[1]->symbol].name);
      err = 1;
    }
    break;

  case FUNC_DECL:
    sym = stab_add(T->value.str, new_alias(), cur_level,
      T->dtype, FUNC, 0);
    if (sym == -EDUPSYMBOL) {
      fault(-EDUPSYMBOL, T->lineno, T->value.str);
      err = 1;
      break;
    }

    T->symbol = sym;
    T->offset = BASE_OFFSET;
    if (T->children[0]) {
      T->children[0]->offset = T->offset;
      err |= sem_check(T->children[0]);
      T->width = T->children[0]->width;
      stab.symbols[sym].param_num = T->children[0]->num;
    }
    break;
  
  case PARAM_LIST:
    T->children[0]->offset = T->offset;
    err |= sem_check(T->children[0]);
    if (T->children[1]) {
      T->children[1]->offset = T->offset + T->children[0]->width;
      err |= sem_check(T->children[1]);
      T->num = T->children[0]->num + T->children[1]->num;
      T->width = T->children[0]->width + T->children[1]->width;
    } else {
      T->num = T->children[0]->num;
      T->width = T->children[0]->width;
    }
    break;
  
  case PARAM_DEC:
    if (T->children[0]->type == T_STRUCT) {
      sem_check_struct(T->children[0]);
    }
    
    sym = stab_add(T->children[1]->value.str, new_alias(),
      1, T->children[0]->type, PARAM, T->offset);
    if (sym == -EDUPSYMBOL) {
      fault(-EDUPSYMBOL, T->lineno, T->value.str);
      err = 1;
    } else {
      // If this param is a struct variable
      if (T->children[0]->symbol) {
        stab.symbols[sym].struct_type = T->children[0]->symbol;
      }
    }
    
    T->children[1]->symbol = sym;
    T->num = 1;
    T->width = WIDTH(T->children[0]->type);
    break;

  case CODE_BLOCK:
    cur_level++;
    stab.scope_begin[stab.cur_scope++] = stab.size;
    T->width = 0;
    if (T->children[0]) {
      T->children[0]->symbol = T->symbol;
      T->children[0]->looping = T->looping;
    }
    err |= sem_check(T->children[0]);
    cur_level--;

#ifdef SHOW_STAB
    // Display the stab before exiting current
    // symbol scope.
    printf("Exiting scope %d:\n", stab.cur_scope);
    stab_display();
#endif

    stab.size = stab.scope_begin[--stab.cur_scope];
    break;
  
  case STMT_LIST:
    if (T->children[0]) {
      T->children[0]->symbol = T->symbol;
      T->children[0]->offset = T->offset;
      T->children[0]->looping = T->looping;
      err |= sem_check(T->children[0]);
      T->width = T->children[0]->width;
    }
    if (T->children[1]) {
      T->children[1]->symbol = T->symbol;
      T->children[1]->offset = T->offset + T->children[0]->width;
      T->children[1]->looping = T->looping;
      err |= sem_check(T->children[1]);
      T->width += T->children[1]->width;
    }
    break;
  
  case IF_THEN:
    T->children[0]->offset = T->children[1]->offset = T->offset;
    err |= sem_check_expr(T->children[0]);
    T->width = T->children[0]->width;
    T->children[1]->symbol = T->symbol;
    T->children[1]->looping = T->looping;
    err |= sem_check(T->children[1]);
    if (T->width < T->children[1]->width)
      T->width = T->children[1]->width;
    break;
 
  case IF_THEN_ELSE:
    T->children[0]->offset = T->children[1]->offset = 
      T->children[2]->offset = T->offset;
    err |= sem_check_expr(T->children[0]);
    T->width = T->children[0]->width;
    T->children[1]->symbol = T->symbol;
    T->children[1]->looping = T->looping;
    err |= sem_check(T->children[1]);
    if (T->width < T->children[1]->width)
      T->width = T->children[1]->width;
    T->children[2]->symbol = T->symbol;
    T->children[2]->looping = T->looping;
    err |= sem_check(T->children[2]);
    if (T->width < T->children[2]->width)
      T->width = T->children[2]->width;
    break;

  case WHILE:
    T->children[0]->offset = T->children[1]->offset = T->offset;
    err |= sem_check_expr(T->children[0]);
    T->width = T->children[0]->width;
    T->children[1]->symbol = T->symbol;
    T->children[1]->looping = 1;
    err |= sem_check(T->children[1]);
    if (T->width < T->children[1]->width)
      T->width = T->children[1]->width;
    break;
    
  case FOR:
    cur_level++;
    stab.scope_begin[stab.cur_scope++] = stab.size;
    T->children[0]->offset = T->children[1]->offset = 
    T->children[2]->offset = T->children[3]->offset = T->offset;
    T->children[0]->symbol = T->symbol;
    T->children[0]->looping = T->looping;
    err |= sem_check(T->children[0]);
    T->width = T->children[0]->width;
    err |= sem_check_expr(T->children[1]);
    if (T->width < T->children[1]->width)
      T->width = T->children[1]->width;
    err |= sem_check_expr(T->children[2]);
    if (T->width < T->children[2]->width)
      T->width = T->children[2]->width;
    T->children[3]->symbol = T->symbol;
    T->children[3]->looping = 1;
    err |= sem_check(T->children[3]);
    if (T->width < T->children[3]->width)
      T->width = T->children[3]->width;
    cur_level--;
    stab.size = stab.scope_begin[--stab.cur_scope];
    break;
    
  case RETURN:
    if (T->children[0]) {
      T->children[0]->offset = T->offset;
      err |= sem_check_expr(T->children[0]);
      T->width=T->children[0]->width;

      // Check return type
      if (T->children[0]->dtype != stab.symbols[T->symbol].dtype) {
        fault(-EWRONGRETTYPE, T->lineno, ast_table[T->children[0]->dtype],
          ast_table[stab.symbols[T->symbol].dtype]);
        err = 1;
      }

    // Check return type void
    } else {
      if (stab.symbols[T->symbol].dtype != T_VOID) {
        fault(-EWRONGRETTYPE, T->lineno,
          "void", ast_table[stab.symbols[T->symbol].dtype]);
        err = 1;
      }
    }

    stab.symbols[T->symbol].returned = 1;
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
  stab.size = 0;
  stab_add("read", "-", 0, T_INT, FUNC, 4);
  stab.symbols[0].param_num = 0;
  stab_add("write", "-", 0, T_INT, FUNC, 4);
  stab.symbols[0].param_num = 1;

  // Initialize the symbol scope.
  stab.scope_begin[0] = 0;
  stab.cur_scope = 1;

  // Do the semantic analysis
  T->offset = 0;
  if (sem_check(T)) {
    exit(1);
  }
}