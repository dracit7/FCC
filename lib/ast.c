
#include <lib/ast.h>

// Allocate a new ast node and return its address.
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

// printf with indent. 
static void idtprintf(int indent, const char* fmt, ...) {
  printf("%*c", indent*INDENT_SIZE, ' ');
  va_list args;
  va_start(args, fmt);
  vprintf(fmt, args);
  va_end(args);
  putchar('\n');
}

#ifdef SHOW_AST
void ast_display(ast_node* t, int indent) {
  if (!t) return;

  switch (t->type) {
	case EXT_DEF_LIST:
    ast_display(t->children[0], indent);
    ast_display(t->children[1], indent);
    break;
	case EXT_VAR_DEF: 
    idtprintf(indent, "Global variable declaration:");
    ast_display(t->children[0], indent+1);
    idtprintf(indent+1, "Variables: ");
    ast_display(t->children[1], indent+2);
    break;
	case T_INT:
	case T_FLOAT:
	case T_CHAR:
	case T_STRING:
	case T_VOID:
    idtprintf(indent, "Type: %s", ast_table[t->type]);
    break;
  case T_STRUCT:
    if (t->children[0]) {
      idtprintf(indent, "Type: %s", ast_table[t->type]);
      if (t->value.str[0])
        idtprintf(indent+1, "Struct name: %s", t->value.str);
      else
        idtprintf(indent+1, "Anonymous struct");
      idtprintf(indent+1, "Members:");
      ast_display(t->children[0], indent+2);
    } else idtprintf(indent, "Type: struct %s", t->value.str);
    break;
  case MEMBER_LIST:
    idtprintf(indent, "***");
    ast_display(t->children[0], indent);
    ast_display(t->children[1], indent);
    ast_display(t->children[2], indent);
    break;
  case EXT_DECL_LIST:
    ast_display(t->children[0], indent);
    ast_display(t->children[1], indent);
    break;
  case STRUCT_DEF:
    idtprintf(indent, "Struct definition:");
    idtprintf(indent+1, "Struct name: %s", t->value.str);
    idtprintf(indent+1, "Members:");
    ast_display(t->children[0], indent+2);
    break;
	case FUNC_DEF:
    idtprintf(indent, "Function declaration:");
    ast_display(t->children[0], indent+1);
    ast_display(t->children[1], indent+1);
    idtprintf(indent+1, "Function body:");
    ast_display(t->children[2], indent+2);
    break;
	case FUNC_DECL:
    idtprintf(indent, "Function name: %s", t->value.str);
    if (t->children[0]) {
      idtprintf(indent, "Parameter list:");
      ast_display(t->children[0], indent);
    } else idtprintf(indent, "No parameter");
    break;
	case PARAM_LIST:
    idtprintf(indent+1, "***");
    ast_display(t->children[0], indent);
    ast_display(t->children[1], indent);
    break;
	case PARAM_DEC:
    ast_display(t->children[0], indent+1);
    ast_display(t->children[1], indent+1);
    break;
  case CODE_BLOCK:
    ast_display(t->children[0], indent);
    break;
	case STMT_LIST:
    ast_display(t->children[0],indent);
    ast_display(t->children[1],indent);
    break;
	case RETURN:
    idtprintf(indent, "Return");
    ast_display(t->children[0], indent+1);
    break;
  case IF_THEN:
    idtprintf(indent, "If");
    ast_display(t->children[0], indent+1);
    idtprintf(indent, "Then");
    ast_display(t->children[1], indent+1);
    break;
  case IF_THEN_ELSE:
    idtprintf(indent, "If");
    ast_display(t->children[0], indent+1);
    idtprintf(indent, "Then");
    ast_display(t->children[1], indent+1);
    idtprintf(indent, "Else");
    ast_display(t->children[2], indent+1);
    break;
  case WHILE:
    idtprintf(indent, "While");
    ast_display(t->children[0], indent+1);
    idtprintf(indent, "Do");
    ast_display(t->children[1], indent+1);
    break;
  case FOR:
    idtprintf(indent, "For loop");
    idtprintf(indent+1, "Initialization:");
    ast_display(t->children[0], indent+2);
    idtprintf(indent+1, "Test expression:");
    ast_display(t->children[1], indent+2);
    idtprintf(indent+1, "Update statement:");
    ast_display(t->children[2], indent+2);
    idtprintf(indent+1, "Loop body:");
    ast_display(t->children[3], indent+2);
    break;
  case VAR_DEF:
    idtprintf(indent, "Local variable declaration:");
    ast_display(t->children[0],indent+1);
    ast_display(t->children[1],indent+1);
    break;
  case DEC_LIST:
    ast_display(t->children[0], indent);
    ast_display(t->children[1], indent);
    break;
  case VAR_INIT:
    idtprintf(indent, "Variable initialization:");
    ast_display(t->children[0],indent+1);
    ast_display(t->children[1],indent+1);
    break;
	case IDENT:
    idtprintf(indent, "Name: %s", t->value.str);
    for (int i = 0; i < t->dim; i++) {
      if (t->capacity[i])
        idtprintf(indent, "Dim %d: capacity %d", i+1, t->capacity[i]);
      else
        idtprintf(indent, "Dim %d: capacity not decleared", i+1);
    }
    break;
  case ARRAY_CALL:
    ast_display(t->children[0], indent);
    idtprintf(indent, "Array index:");
    ast_display(t->children[1], indent+1);
    break;
  case MEMBER_CALL:
    idtprintf(indent, "Get struct member:");
    ast_display(t->children[0], indent+1);
    idtprintf(indent+1, "Member: %s", t->value.str);
    break;
	case L_INT:
    idtprintf(indent, "%s: %d", ast_table[T_INT], t->value.itg);
    break;
	case L_CHAR:
    idtprintf(indent, "%s: '%c'", ast_table[T_CHAR], t->value.itg);
    break;
	case L_FLOAT:
    idtprintf(indent, "%s: %f", ast_table[T_FLOAT], t->value.flt);
    break;
	case L_STRING:
    idtprintf(indent, "%s: %s", ast_table[T_STRING], t->value.str);
    break;
	case ASSIGN:
    idtprintf(indent, "Assign");
    idtprintf(indent+1, "From:");
    ast_display(t->children[1], indent+2);
    idtprintf(indent+1, "To:");
    ast_display(t->children[0], indent+2);
    break;
	case COMP_ASSIGN:
    idtprintf(indent, "Assign (%s)", t->value.str);
    idtprintf(indent+1, "From:");
    ast_display(t->children[1], indent+2);
    idtprintf(indent+1, "To:");
    ast_display(t->children[0], indent+2);
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
    idtprintf(indent, "%s", ast_table[t->type]);
    ast_display(t->children[0],indent+1);
    ast_display(t->children[1],indent+1);
    break;
	case OP_NOT:
  case OP_INC:
  case OP_DEC:
	case UMINUS:
    idtprintf(indent, "%s", ast_table[t->type]);
    ast_display(t->children[0],indent+1);
    break;
  case FUNC_CALL:
    idtprintf(indent, "Function call");
    idtprintf(indent+1, "Function name: %s", t->value.str);
    if (t->children[0]) {
      idtprintf(indent+1, "Arguments:");
      ast_display(t->children[0],indent+2);
    } else idtprintf(indent+1, "No argument");
    break;
	case ARG_LIST:
    ast_display(t->children[0], indent);
    ast_display(t->children[1], indent);
    break;
  }
}
#else
void ast_display(ast_node* t, int indent) {}
#endif