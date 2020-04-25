
#ifndef _LEXER_H
#define _LEXER_H

#include <lib/parser.h>

static const char* token_table[] = {
  [T_CHAR] = "T_CHAR",
  [T_INT] = "T_INT",
  [T_FLOAT] = "T_FLOAT",
  [T_STRING] = "T_STRING",
  [T_STRUCT] = "T_STRUCT",
  [T_VOID] = "T_VOID",

  [59] = "';'",
  [44] = "','",
  [40] = "'('",
  [41] = "')'",
  [91] = "'['",
  [93] = "']'",
  [123] = "'{'",
  [125] = "'}'",

  [OP_ADD] = "OP_ADD",
  [OP_SUB] = "OP_SUB",
  [OP_STAR] = "OP_STAR",
  [OP_DIV] = "OP_DIV",
  [OP_MOD] = "OP_MOD",
  [OP_NOT] = "OP_NOT",
  [OP_DOT] = "OP_DOT",

  [OP_G] = "OP_G",
  [OP_L] = "OP_L",
  [OP_GE] = "OP_GE",
  [OP_LE] = "OP_LE",
  [OP_EQ] = "OP_EQ",
  [OP_NEQ] = "OP_NEQ",
  [OP_AND] = "OP_AND",
  [OP_OR] = "OP_OR",
  [OP_INC] = "OP_INC",
  [OP_DEC] = "OP_DEC",

  [ASSIGN] = "ASSIGN",
  [COMP_ASSIGN] = "COMP_ASSIGN",

  [IF] = "IF",
  [ELSE] = "ELSE",
  [RETURN] = "RETURN",
  [WHILE] = "WHILE",
  [BREAK] = "BREAK",
  [CONTINUE] = "CONTINUE",

  [L_INT] = "L_INT",
  [L_FLOAT] = "L_FLOAT",
  [L_STRING] = "L_STRING",

  [IDENT] = "IDENT",
};

#endif