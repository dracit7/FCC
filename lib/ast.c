
#include <lib/ast.h>

char* ast_table[] = {
  [T_INT] = "int",
  [T_FLOAT] = "float",
  [T_CHAR] = "char",
  [T_STRING] = "string",
  [T_STRUCT] = "struct",
  [T_VOID] = "void",
  [OP_AND] = "Logic and",
  [OP_OR] = "Logic or",
  [OP_NOT] = "Logic not",
  [OP_ADD] = "Add",
  [OP_SUB] = "Substract",
  [OP_STAR] = "Multiply",
  [OP_DIV] = "Division",
  [OP_MOD] = "Mod",
  [OP_G] = "Is greater than",
  [OP_L] = "Is less than",
  [OP_GE] = "Is greater than or equal to",
  [OP_LE] = "Is less than or equal to",
  [OP_EQ] = "Is equal to",
  [OP_NEQ] = "Is not equal to",
  [OP_INC] = "Increase by 1",
  [OP_DEC] = "Decrease by 1",
  [UMINUS] = "Negative",
};

ast_node* ast_new_node(int child_num, int type, int pos, ...) {

  // Allocate a new node.
  ast_node* t = malloc(sizeof(ast_node));
  memset(t, 0, sizeof(ast_node));
  t->type = type;
  t->lineno = pos;

  // Set children.
  va_list va;
  va_start(va, pos);
  for (int i = 0; i < child_num; i++) {
    t->children[i] = va_arg(va, ast_node*);
  }
  va_end(va);
  
  return t;
}

// Do indent
static void do_indent(int indent) {
  printf("%*c", indent, ' ');
}

static void ast_show(int indent, const char* fmt, ...) {

#ifdef SHOW_AST
  do_indent(indent*INDENT_SIZE);
  va_list args;
  va_start(args, fmt);
  vprintf(fmt, args);
  va_end(args);
  putchar('\n');
#endif

}

void ast_trav(ast_node* t, int indent) {
  if (!t) return;

  switch (t->type) {
	case EXT_DEF_LIST:
    ast_trav(t->children[0], indent);
    ast_trav(t->children[1], indent);
    break;
	case EXT_VAR_DEF: 
    ast_show(indent, "Global variable declaration:");
    ast_trav(t->children[0], indent+1);
    ast_show(indent+1, "Variables: ");
    ast_trav(t->children[1], indent+2);
    break;
	case T_INT:
	case T_FLOAT:
	case T_CHAR:
	case T_STRING:
	case T_VOID:
    ast_show(indent, "Type: %s", ast_table[t->type]);
    break;
  case T_STRUCT:
    if (t->children[0]) {
      ast_show(indent, "Type: %s", ast_table[t->type]);
      if (t->value.str[0])
        ast_show(indent+1, "Struct name: %s", t->value.str);
      else
        ast_show(indent+1, "Anonymous struct");
      ast_show(indent+1, "Members:");
      ast_trav(t->children[0], indent+2);
    } else ast_show(indent, "Type: struct %s", t->value.str);
    break;
  case MEMBER_LIST:
    ast_show(indent, "***");
    ast_trav(t->children[0], indent);
    ast_trav(t->children[1], indent);
    ast_trav(t->children[2], indent);
    break;
  case EXT_DECL_LIST:
    ast_trav(t->children[0], indent);
    ast_trav(t->children[1], indent);
    break;
  case STRUCT_DEF:
    ast_show(indent, "Struct definition:");
    ast_show(indent+1, "Struct name: %s", t->value.str);
    ast_show(indent+1, "Members:");
    ast_trav(t->children[0], indent+2);
    break;
	case FUNC_DEF:
    ast_show(indent, "Function declaration:");
    ast_trav(t->children[0], indent+1);
    ast_trav(t->children[1], indent+1);
    ast_show(indent+1, "Function body:");
    ast_trav(t->children[2], indent+2);
    break;
	case FUNC_DECL:
    ast_show(indent, "Function name: %s", t->value.str);
    if (t->children[0]) {
      ast_show(indent, "Parameter list:");
      ast_trav(t->children[0], indent);
    } else ast_show(indent, "No parameter");
    break;
	case PARAM_LIST:
    ast_show(indent+1, "***");
    ast_trav(t->children[0], indent);
    ast_trav(t->children[1], indent);
    break;
	case PARAM_DEC:
    ast_trav(t->children[0], indent+1);
    ast_trav(t->children[1], indent+1);
    break;
	case STMT_LIST:
    ast_trav(t->children[0],indent);
    ast_trav(t->children[1],indent);
    break;
	case RETURN:
    ast_show(indent, "Return");
    ast_trav(t->children[0], indent+1);
    break;
  case IF_THEN:
    ast_show(indent, "If");
    ast_trav(t->children[0], indent+1);
    ast_show(indent, "Then");
    ast_trav(t->children[1], indent+1);
    break;
  case IF_THEN_ELSE:
    ast_show(indent, "If");
    ast_trav(t->children[0], indent+1);
    ast_show(indent, "Then");
    ast_trav(t->children[1], indent+1);
    ast_show(indent, "Else");
    ast_trav(t->children[2], indent+1);
    break;
  case WHILE:
    ast_show(indent, "While");
    ast_trav(t->children[0], indent+1);
    ast_show(indent, "Do");
    ast_trav(t->children[1], indent+1);
    break;
  case FOR:
    ast_show(indent, "For loop");
    ast_show(indent+1, "Initialization:");
    ast_trav(t->children[0], indent+2);
    ast_show(indent+1, "Test expression:");
    ast_trav(t->children[1], indent+2);
    ast_show(indent+1, "Update statement:");
    ast_trav(t->children[2], indent+2);
    ast_show(indent+1, "Loop body:");
    ast_trav(t->children[3], indent+2);
    break;
  case VAR_DEF:
    ast_show(indent, "Local variable declaration:");
    ast_trav(t->children[0],indent+1);
    ast_trav(t->children[1],indent+1);
    break;
  case DEC_LIST:
    ast_trav(t->children[0], indent);
    ast_trav(t->children[1], indent);
    break;
  case VAR_INIT:
    ast_show(indent, "Variable initialization:");
    ast_trav(t->children[0],indent+1);
    ast_trav(t->children[1],indent+1);
    break;
	case IDENT:
    ast_show(indent, "Name: %s", t->value.str);
    for (int i = 0; i < t->dim; i++) {
      if (t->capacity[i])
        ast_show(indent, "Dim %d: capacity %d", i+1, t->capacity[i]);
      else
        ast_show(indent, "Dim %d: capacity not decleared", i+1);
    }
    break;
  case ARRAY_CALL:
    ast_trav(t->children[0], indent);
    ast_show(indent, "Array index:");
    ast_trav(t->children[1], indent+1);
    break;
  case MEMBER_CALL:
    ast_show(indent, "Get struct member:");
    ast_trav(t->children[0], indent+1);
    ast_show(indent+1, "Member: %s", t->value.str);
    break;
	case L_INT:
    ast_show(indent, "%s: %d", ast_table[T_INT], t->value.itg);
    break;
	case L_FLOAT:
    ast_show(indent, "%s: %f", ast_table[T_FLOAT], t->value.flt);
    break;
	case L_STRING:
    ast_show(indent, "%s: %s", ast_table[T_STRING], t->value.str);
    break;
	case ASSIGN:
    ast_show(indent, "Assign to %s:", t->value.str);
    ast_trav(t->children[0], indent+1);
    break;
	case COMP_ASSIGN:
    ast_show(indent, "%s:", t->value.str);
    ast_trav(t->children[0], indent+1);
    break;
	case OP_AND:
	case OP_OR:
	case OP_ADD:
	case OP_SUB:
	case OP_STAR:
	case OP_DIV:
	case OP_MOD:
  case OP_G:
  case OP_L:
  case OP_GE:
  case OP_LE:
  case OP_EQ:
  case OP_NEQ:
    ast_show(indent, "%s", ast_table[t->type]);
    ast_trav(t->children[0],indent+1);
    ast_trav(t->children[1],indent+1);
    break;
	case OP_NOT:
  case OP_INC:
  case OP_DEC:
	case UMINUS:
    ast_show(indent, "%s", ast_table[t->type]);
    ast_trav(t->children[0],indent+1);
    break;
  case FUNC_CALL:
    ast_show(indent, "Function call");
    ast_show(indent+1, "Function name: %s", t->value.str);
    if (t->children[0]) {
      ast_show(indent+1, "Arguments:");
      ast_trav(t->children[0],indent+2);
    } else ast_show(indent+1, "No argument");
    break;
	case ARG_LIST:
    ast_trav(t->children[0], indent);
    ast_trav(t->children[1], indent);
    break;
  }
}