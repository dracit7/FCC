
%option yylineno

%{
#include <inc/ds.h>
#include <lib/parser.h>

int yycolumn = 1;

void lexer_routine();
#define YY_USER_ACTION lexer_routine();
%}

/* Operators */
OP_G [>]
OP_L [<]
OP_GE [>][=]
OP_LE [<][=]
OP_EQ [=][=]
OP_NEQ [!][=]

OP_AND [&][&]
OP_OR [|][|]

OP_INC [+][+]
OP_DEC [-][-]

ASSIGN [=]
COMP_ASSIGN [+\-*/%][=]

/* Keywords */
IF if
ELSE else 
RETURN return
WHILE while
BREAK break
CONTINUE continue

/* Literals */
L_INT -?[1-9][0-9]*|[0]
L_HINT -?[0][Xx]([1-9][0-9]*|[0])
L_OINT -?[0][0-7]
L_FLOAT -?[0-9]*[.][0-9]+([eE][+\-]?[0-9]*|[0])?f?
L_CHAR '([^'\\\n]|\\.)'
L_STRING ["]([^"\\\n]|\\.|\\\n)*["]

/* Others */
COMMENT [/][/].*[\n]|[/][*].*[*][/]

%%
  /* Data types */
char {return T_CHAR;}
int {return T_INT;}
float {return T_FLOAT;}
string {return T_STRING;}
struct {return T_STRUCT;}
void {return T_VOID;}

  /* Operators */
[;,()\[\]{}] {return yytext[0];}
[+] {return OP_ADD;}
[\-] {return OP_SUB;}
[*] {return OP_STAR;}
[/] {return OP_DIV;}
[%] {return OP_MOD;}
[!] {return OP_NOT;}
[.] {return OP_DOT;}
{OP_G} {return OP_G;}
{OP_L} {return OP_L;}
{OP_GE} {return OP_GE;}
{OP_LE} {return OP_LE;}
{OP_EQ} {return OP_EQ;}
{OP_NEQ} {return OP_NEQ;}
{OP_AND} {return OP_AND;}
{OP_OR} {return OP_OR;}
{OP_INC} {return OP_INC;}
{OP_DEC} {return OP_DEC;}
{ASSIGN} {return ASSIGN;}
{COMP_ASSIGN} {
  yylval.str = strdup(yytext);
  return COMP_ASSIGN;
}

  /* Keywords */
{IF} {return IF;}
{ELSE} {return ELSE;}
{RETURN} {return RETURN;}
{WHILE} {return WHILE;}
{BREAK} {return BREAK;}
{CONTINUE} {return CONTINUE;}

	/* Literals */
{L_INT} {
  yylval.integer = strtol(yytext, NULL, 10);
  return L_INT;
}

{L_CHAR} {
  yylval.integer = yytext[1];
  return L_INT;
}

{L_OINT} {
  yylval.integer = strtol(yytext+1, NULL, 8);
  return L_INT;
}

{L_HINT} {
  yylval.integer = strtol(yytext+2, NULL, 16);
  return L_INT;
}

{L_FLOAT} {
  yylval.floatpoint = atof(yytext);
  return L_FLOAT;
}

{L_STRING} {
  yylval.str = strdup(yytext);
  return L_STRING;
}

  /* Identifiers */
[a-zA-Z][a-zA-Z0-9_]* {
  yylval.str = strdup(yytext);
  return IDENT;
}

  /* Spaces & Comments */
{COMMENT} {}
[\t\r ] {}

[\n] {yycolumn = 1;}

. {
  printf("Error: unregonized word %s(%d) at line %d\n", 
  yytext, yytext[0], yylineno);
}

%%

int yywrap() {return 1;}

void lexer_routine() {
  yylloc.first_line = yylloc.last_line = yylineno;
  yylloc.first_column = yycolumn;
  yylloc.last_column = yycolumn + yyleng - 1;
  yycolumn += yyleng;
}