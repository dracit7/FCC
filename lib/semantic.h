
#ifndef _SEMANTIC_H
#define _SEMANTIC_H

#define WIDTH(type) \
  ((type == T_INT || type == T_FLOAT) ? 4 : (\
  (type == T_CHAR) ? 1 : sizeof(char *)))

#define _border "----------------------------------------"
#define PRINT_BORDER() printf("+%.*s+%.*s+%.*s+%.*s+%.*s+%.*s+\n",\
  15,_border, 10,_border, 7,_border, 8,_border, 12,_border, 8,_border)

void semantic_analysis(ast_node* T);
void stab_display();

#endif