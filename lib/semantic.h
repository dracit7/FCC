
#ifndef _SEMANTIC_H
#define _SEMANTIC_H

// Width of data types.
#define WIDTH(type) \
  ((type == T_INT || type == T_FLOAT) ? 4 : (\
  (type == T_CHAR) ? 1 : sizeof(char *)))

// For printing the symbol table.
#define _border "----------------------------------------"
#define PRINT_BORDER() printf("+%.*s+%.*s+%.*s+%.*s+%.*s+%.*s+%.*s+\n",\
  4,_border, 15,_border, 7,_border, 7,_border, 8,_border, 11,_border, 8,_border)

/* 
 * Define some abbreviations to simplify my work.
 * These abbreviations should not be used out of semantic.c.
 */

// The ith scope in the scope stack.
#define SCOPE(i) (NTH(stab.scopes, NTH(stab.stack, i)))
// The index of current scope in the scope stack.
#define CUR_SCOPE (LEN(stab.stack)-1)
// The jth symbol in the ith scope.
#define SYMBOL(index) (SCOPE(SCOPE_I(index)).symbols[SYMBOL_I(index)])

// Push a new scope into the scope stack.
#define SCOPE_PUSH() do {\
  symbol_scope s = {0};\
  LIST_PUSH(stab.scopes, s, symbol_scope);\
  LIST_PUSH(stab.stack, stab.scopes->len-1, int);\
} while (0)

// Pop a scope out of the scope stack.
// If we want to show the symbol table, we need to
// show it each time we pop a scope out.
#ifdef SHOW_STAB
#define SCOPE_POP() do {\
  printf("Exiting scope %d:\n", CUR_SCOPE);\
  stab_display();\
  LIST_POP(stab.stack);\
} while (0)
#else
#define SCOPE_POP() do {\
  LIST_POP(stab.stack);\
} while (0)
#endif

// Return the clone of the scope stack in form of array.
//
// The length of stack is placed in the first element
// of returned array, and the content of stack starts
// from the second element.
#define STACK_CLONE(list) ({\
  int* l = (int *)malloc(sizeof(int)*((list)->len+1));\
  for (int i = 1; i <= (list)->len; i++)\
    l[i] = NTH(list, i-1);\
  l[0] = (list)->len;\
  (l);\
})

void semantic_analysis(ast_node* T);
void stab_display();
st_index stab_search(char *name);

#endif