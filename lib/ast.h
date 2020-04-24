
#ifndef _AST_H
#define _AST_H

#include <inc/ds.h>
#include <lib/parser.h>

#include <malloc.h>
#include <string.h>
#include <stdarg.h>

extern char* ast_table[];

ast_node* ast_new_node(int child_num, int type, int pos, ...);
void ast_trav(ast_node* t, int indent);

#endif