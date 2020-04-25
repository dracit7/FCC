/* A Bison parser, made by GNU Bison 3.5.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_YY_LIB_PARSER_H_INCLUDED
# define YY_YY_LIB_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    T_CHAR = 258,
    T_INT = 259,
    T_FLOAT = 260,
    T_STRING = 261,
    T_VOID = 262,
    ASSIGN = 263,
    COMP_ASSIGN = 264,
    OP_OR = 265,
    OP_AND = 266,
    OP_EQ = 267,
    OP_NEQ = 268,
    OP_G = 269,
    OP_L = 270,
    OP_GE = 271,
    OP_LE = 272,
    OP_ADD = 273,
    OP_SUB = 274,
    OP_STAR = 275,
    OP_DIV = 276,
    OP_MOD = 277,
    OP_NOT = 278,
    OP_INC = 279,
    OP_DEC = 280,
    UMINUS = 281,
    IF = 282,
    ELSE = 283,
    RETURN = 284,
    WHILE = 285,
    BREAK = 286,
    CONTINUE = 287,
    IDENT = 288,
    L_INT = 289,
    L_FLOAT = 290,
    L_STRING = 291,
    EXT_DEF_LIST = 292,
    EXT_VAR_DEF = 293,
    FUNC_DEF = 294,
    EXT_DECL_LIST = 295,
    FUNC_DECL = 296,
    PARAM_LIST = 297,
    PARAM_DEC = 298,
    STMT_LIST = 299,
    IF_THEN = 300,
    IF_THEN_ELSE = 301,
    VAR_DEF = 302,
    DEC_LIST = 303,
    FUNC_CALL = 304,
    ARG_LIST = 305,
    ARRAY_CALL = 306,
    VAR_INIT = 307,
    NO_ELSE = 308
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 23 "scripts/parser.y"

  int integer;
  float floatpoint;
  char* str;
  ast_node* node;

#line 118 "lib/parser.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (void);

#endif /* !YY_YY_LIB_PARSER_H_INCLUDED  */
