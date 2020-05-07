
#ifndef _DS_H
#define _DS_H

#include <stdint.h>
#include <inc/const.h>

// The node of AST.
//
// Use a binary linked list to implement the tree.
typedef struct _node {
  int type;

  // Value of this node, only valid in leaves.
  union {
    char str[MAX_IDENT_LEN];
    double flt;
    uint64_t itg;
  } value;

  // Dim and capacity of this node, only valid in arrays.
  int dim;
  int capacity[MAX_ARRAY_DIM];

  // Children of this node.
  struct _node* children[MAX_CHILD_NUM];

  // Line number information.
  int lineno;

  // Members used in semantic analysis.
  int dtype; // Identifier's datatype. 
  int symbol; // The index in the symbol table.
  int num; // Number of parameters of variables.
  int looping; // If we're in a loop.

  // Symbol index of the parent structure of
  // this variable.
  int parent_struct;

  // Members for generating TAC.
  int offset; // Offset in the segment.
  int width; // Bit width.

} ast_node;

// The symbol table entry.
typedef struct {
  int level;

  // Data type and symbol type of this symbol.
  int dtype;
  unsigned int stype:3;

  // Name and alias of this symbol.
  char name[MAX_IDENT_LEN];
  char alias[MAX_ALIAS_LEN];

  // The number of paramaters.
  int param_num;

  // The offset in the segment, useful when generating
  // object code.
  int offset;

  // Is this variable an array?
  unsigned int isarray:1;

  // If this symbol is a function, is it renturned?
  unsigned int returned:1;

  // If parent_struct==x, x is the struct this symbol belongs to.
  // If parent_struct==NONE, this symbol is not a member.
  int parent_struct;

  // If this symbol is a struct variable,
  // this member indicates the index of the
  // corresponding struct symbol.
  int struct_type;

} symbol_table_entry;

// The symbol table.
typedef struct {
  symbol_table_entry symbols[MAX_SYMBOLTABLE_SIZE];
  int size;

  // The scopes of symbol table.
  int scope_begin[MAX_SYMBOLSCOPE_NUM];
  int cur_scope;
} symbol_table;

enum symbol_types {
  FUNC, VAR, PARAM, TEMP, STRUCT
};

static const char* symbol_name[] = {
  [FUNC] = "function",
  [VAR] = "variable",
  [PARAM] = "parameter",
  [TEMP] = "literal",
  [STRUCT] = "struct",
};

#endif