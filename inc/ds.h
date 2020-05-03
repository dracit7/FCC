
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

  // Line number information
  int lineno;

} ast_node;

#endif