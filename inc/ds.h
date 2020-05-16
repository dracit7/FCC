
#ifndef _DS_H
#define _DS_H

#include <stdint.h>
#include <inc/const.h>

#include <llvm-c/Core.h>

/*
 * The symbol table
 * 
 * We organize the symbol table in a form of scope
 * stack - each scope only contains symbols declared
 * in itself, and all symbols in current stack is
 * visible to current scope.
 * 
 * When we enter a new scope, we store it in the scope
 * array and push its id to the scope stack. Similarly,
 * we pop the scope id when we exit.
 * 
 * In this form, the scope layer is naturally represented
 * by the index of stack, so we don't need the `level`
 * field in symbol_table_entry.
 * 
 * The structure of scope stack:
 * 
 * +--------------------------------+
 * |        Global symbols          |
 * +--------------------------------+
 * | Parameters of current function |
 * +--------------------------------+
 * |              ...               |
 * +--------------------------------+    
 */

// The index of the symbol table.
typedef uint64_t st_index;
#define ST_INDEX(i, j) ((((uint64_t)i)<<32)^((uint64_t)j))
#define SCOPE_I(index) ((uint32_t)(index>>32))
#define SYMBOL_I(index) ((uint32_t)(index))

// The symbol table entry.
typedef struct {

  // Data type and symbol type of this symbol.
  int dtype;
  unsigned int stype:3;

  // Name and alias of this symbol.
  char name[MAX_IDENT_LEN];
  char alias[MAX_ALIAS_LEN];

  // Function attributes.
  int param_num; // The number of paramaters.
  int param_scope; // The scope id of function's params.

  // Array dimension and capacity.
  int dim;
  int capacity[MAX_ARRAY_DIM];

  // If this symbol is a function, is it renturned?
  unsigned int returned:1;

  // If parent_struct==x, x is the struct this symbol belongs to.
  // If parent_struct==NONE, this symbol is not a member.
  st_index parent_struct;

  // If this symbol is a struct variable,
  // this member indicates the index of the
  // corresponding struct symbol.
  st_index struct_type;

  // Reference in LLVM.
  LLVMTypeRef llvm_type;
  LLVMValueRef llvm_value;

} symbol_table_entry;

// A scope of the symbol table.
typedef struct {
  symbol_table_entry symbols[MAX_SYMBOLTABLE_SIZE];
  int size;
} symbol_scope;

// Stack of scope indexes.
typedef struct {
  int* arr;
  uint32_t len;
  uint32_t cap;
} index_list;

// Stack of scopes.
typedef struct {
  symbol_scope* arr;
  uint32_t len;
  uint32_t cap;
} scope_list;

// The symbol table.
typedef struct {
  scope_list* scopes;
  index_list* stack;
} symbol_table;

// The types of symbols.
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

/*
 * Data structures to fit up with LLVM.
 * 
 * We use LLVM to generate IR code and target code.
 */

// List of LLVMTypeRef.
typedef struct {
  LLVMTypeRef* arr;
  uint32_t len;
  uint32_t cap;
} type_list;

// List of LLVMValueRef.
typedef struct {
  LLVMValueRef* arr;
  uint32_t len;
  uint32_t cap;
} value_list;

/*
 * AST
 */

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

  // Dim and capacity of this node.
  int dim;
  int capacity[MAX_ARRAY_DIM];

  // Children of this node.
  struct _node* children[MAX_CHILD_NUM];

  // Line number information.
  int lineno;

  // Members used in semantic analysis.
  st_index symbol; // The index in the symbol table.
  int dtype; // Identifier's datatype. 
  int num; // Number of parameters of variables.
  unsigned looping:1; // If we're in a loop.
  unsigned external:1; // If the variable is external.

  // Symbol index of the parent structure of
  // this variable.
  st_index parent_struct;

  // Member for LLVM.
  LLVMTypeRef llvm_type;
  LLVMValueRef llvm_value;
  LLVMBasicBlockRef llvm_before;
  LLVMBasicBlockRef llvm_after;
  type_list* llvm_argtypes;
  value_list* llvm_args;

} ast_node;

/*
 * A set of list API
 */

// Allocate a new list and return its address.
#define LIST_NEW(list_type, element_type) ({\
  list_type* l = (list_type *)malloc(sizeof(list_type));\
  l->arr = (element_type *)malloc(sizeof(element_type)*LIST_INIT_SIZE);\
  memset(l->arr, 0, LIST_INIT_SIZE);\
  l->len = 0;\
  l->cap = LIST_INIT_SIZE;\
  (l);\
})

// Length and index functions.
#define LEN(list) ((list)->len)
#define NTH(list, n) ((list)->arr[n])

// Stack functions.
#define LIST_TOP(list) NTH(list, LEN(list)-1)
#define LIST_POP(list) ((list)->len--)
#define LIST_PUSH(list, element, element_type) do {\
  if ((list)->len == (list)->cap) {\
    (list)->cap *= 2;\
    (list)->arr = (element_type *)realloc((list)->arr, sizeof(element_type)*(list)->cap);\
    memset((list)->arr, 0, (list)->cap);\
  }\
  (list)->arr[(list)->len++] = element;\
} while (0)

// Free the list.
#define LIST_FREE(list) do {\
  free((list)->arr);\
  free(list);\
} while (0)

#endif