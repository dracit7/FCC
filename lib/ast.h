
#ifndef _AST_H
#define _AST_H

#include <inc/ds.h>
#include <lib/parser.h>
#include <lib/log.h>

#include <malloc.h>
#include <string.h>
#include <stdarg.h>

static const char* ast_table[] = {
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

ast_node* ast_new_node(int child_num, int type, int pos, ...);
void ast_display(ast_node* t, int indent);

#endif