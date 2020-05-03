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
    T_STRUCT = 262,
    T_VOID = 263,
    ASSIGN = 264,
    COMP_ASSIGN = 265,
    OP_OR = 266,
    OP_AND = 267,
    OP_EQ = 268,
    OP_NEQ = 269,
    OP_G = 270,
    OP_L = 271,
    OP_GE = 272,
    OP_LE = 273,
    OP_ADD = 274,
    OP_SUB = 275,
    OP_STAR = 276,
    OP_DIV = 277,
    OP_MOD = 278,
    OP_NOT = 279,
    OP_INC = 280,
    OP_DEC = 281,
    UMINUS = 282,
    OP_DOT = 283,
    IF = 284,
    ELSE = 285,
    RETURN = 286,
    WHILE = 287,
    FOR = 288,
    BREAK = 289,
    CONTINUE = 290,
    IDENT = 291,
    L_INT = 292,
    L_FLOAT = 293,
    L_STRING = 294,
    EXT_DEF_LIST = 295,
    EXT_VAR_DEF = 296,
    FUNC_DEF = 297,
    EXT_DECL_LIST = 298,
    FUNC_DECL = 299,
    PARAM_LIST = 300,
    PARAM_DEC = 301,
    STMT_LIST = 302,
    IF_THEN = 303,
    IF_THEN_ELSE = 304,
    VAR_DEF = 305,
    DEC_LIST = 306,
    FUNC_CALL = 307,
    ARG_LIST = 308,
    ARRAY_CALL = 309,
    VAR_INIT = 310,
    MEMBER_LIST = 311,
    STRUCT_DEF = 312,
    MEMBER_CALL = 313,
    NO_ELSE = 314
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

#line 124 "lib/parser.h"

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
