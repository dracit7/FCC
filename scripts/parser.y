
%debug
%locations

%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <inc/ds.h>

#include <lib/ast.h>

extern int yylineno;

int yylex();
void yyerror(const char* fmt, ...);

%}

// Value types
%union {
  int integer;
  float floatpoint;
  char* str;
  ast_node* node;
}

// Datatypes
%token T_CHAR
%token T_INT
%token T_FLOAT
%token T_STRING
%token T_VOID

// Operators
// 
// Operators that're declared latter has
// higher priority.
%left ASSIGN COMP_ASSIGN
%left OP_OR
%left OP_AND
%left OP_EQ OP_NEQ
%left OP_G OP_L OP_GE OP_LE 
%left OP_ADD OP_SUB
%left OP_STAR OP_DIV OP_MOD
%right OP_NOT OP_INC OP_DEC UMINUS

// Keywords for control
%token IF
%token ELSE
%token RETURN
%token WHILE
%token BREAK
%token CONTINUE

// Identifiers
%token <str> IDENT

// Literals
%token <integer> L_INT
%token <floatpoint> L_FLOAT
%token <str> L_STRING

// Some node types
%token EXT_DEF_LIST EXT_VAR_DEF FUNC_DEF
  EXT_DECL_LIST FUNC_DECL PARAM_LIST PARAM_DEC
  STMT_LIST IF_THEN IF_THEN_ELSE VAR_DEF
  DEC_LIST FUNC_CALL ARG_LIST

// Precedence for resolving the ambiguity
// between if-else and if
%nonassoc NO_ELSE

// Nonterminals
%type <node> program ext_def_list ext_def
  var_type ext_decl_list var_name func_decl
  param_list param code_block stmt_list stmt
  decl decl_list var_decl expr arg_list type_void

%start program

%%

program: ext_def_list 
    {ast_trav($1, 1);}
  ; 

ext_def_list: ext_def ext_def_list
    {$$ = ast_new_node(2, EXT_DEF_LIST, yylineno, $1, $2);}
  | {$$ = NULL;}
  ;  

ext_def: var_type ext_decl_list ';' 
    {$$ = ast_new_node(2, EXT_VAR_DEF, yylineno, $1, $2);}
  | var_type func_decl code_block 
    {$$ = ast_new_node(3, FUNC_DEF, yylineno, $1, $2, $3);}
  | type_void func_decl code_block 
    {$$ = ast_new_node(3, FUNC_DEF, yylineno, $1, $2, $3);}
  ;

type_void: T_VOID
    {$$ = ast_new_node(0, T_VOID, yylineno);}
  ;

var_type: T_INT
    {$$ = ast_new_node(0, T_INT, yylineno);}
  | T_FLOAT {$$ = ast_new_node(0, T_FLOAT, yylineno);}
  | T_CHAR {$$ = ast_new_node(0, T_CHAR, yylineno);}
  | T_STRING {$$ = ast_new_node(0, T_STRING, yylineno);}
  ;      

ext_decl_list: var_decl {$$ = $1;}
  | var_decl ',' ext_decl_list
    {$$ = ast_new_node(2, EXT_DECL_LIST, yylineno, $1, $3);}
  ;  

var_name: IDENT {
    $$ = ast_new_node(0, IDENT, yylineno);
    strcpy($$->value.str, $1);
  }
  ;

func_decl: IDENT '(' param_list ')' {
    $$ = ast_new_node(1, FUNC_DECL, yylineno, $3);
    strcpy($$->value.str, $1);
  }
  | IDENT '(' ')' {
    $$ = ast_new_node(0, FUNC_DECL, yylineno);
    strcpy($$->value.str, $1);
  }
  ;  

param_list: param 
    {$$ = ast_new_node(1, PARAM_LIST, yylineno, $1);}
  | param ',' param_list
    {$$ = ast_new_node(2, PARAM_LIST, yylineno, $1, $3);}
  ;

param: var_type var_name
    {$$ = ast_new_node(2, PARAM_DEC, yylineno, $1, $2);}
  ;

code_block: '{' stmt_list '}'
    {$$ = $2;}
  ;

stmt_list: {$$ = NULL;}  
  | stmt stmt_list {$$ = ast_new_node(2, STMT_LIST, yylineno, $1, $2);}
  | decl stmt_list {$$ = ast_new_node(2, STMT_LIST, yylineno, $1, $2);}
  ;

stmt: expr ';' 
    {$$ = $1;}
  | code_block
    {$$ = $1;}
  | RETURN expr ';'
    {$$ = ast_new_node(1, RETURN, yylineno, $2);}
  | IF '(' expr ')' stmt %prec NO_ELSE
    {$$ = ast_new_node(2, IF_THEN, yylineno, $3, $5);}
  | IF '(' expr ')' stmt ELSE stmt 
    {$$ = ast_new_node(3, IF_THEN_ELSE, yylineno, $3, $5, $7);}
  | WHILE '(' expr ')' stmt
    {$$ = ast_new_node(2, WHILE, yylineno, $3, $5);}
  | BREAK ';'
    {$$ = ast_new_node(0, BREAK, yylineno);}
  | CONTINUE ';'
    {$$ = ast_new_node(0, CONTINUE, yylineno);}
  ;

decl: var_type decl_list ';'
    {$$ = ast_new_node(2, VAR_DEF, yylineno, $1, $2);}
  ;

decl_list: var_decl {$$ = $1;}
  | var_decl ',' decl_list
    {$$ = ast_new_node(2, DEC_LIST, yylineno, $1, $3);}
	;

var_decl: var_name {$$ = $1;}
  | var_name ASSIGN expr
    {$$ = ast_new_node(2, ASSIGN, yylineno, $1, $3);}
  ;

expr: IDENT ASSIGN expr {
    $$ = ast_new_node(1, ASSIGN, yylineno, $3);
    strcpy($$->value.str, $1);
  }
  | expr OP_AND expr 
    {$$ = ast_new_node(2, OP_AND, yylineno, $1, $3);}
  | expr OP_OR expr 
    {$$ = ast_new_node(2, OP_OR, yylineno, $1, $3);}
  | expr OP_ADD expr
    {$$ = ast_new_node(2, OP_ADD, yylineno, $1, $3);}
  | expr OP_SUB expr
    {$$ = ast_new_node(2, OP_SUB, yylineno, $1, $3);}
  | expr OP_STAR expr
    {$$ = ast_new_node(2, OP_STAR, yylineno, $1, $3);}
  | expr OP_DIV expr
    {$$ = ast_new_node(2, OP_DIV, yylineno, $1, $3);}
  | expr OP_MOD expr
    {$$ = ast_new_node(2, OP_MOD, yylineno, $1, $3);}
  | '(' expr ')' 
    {$$ = $2;}
  | OP_SUB expr %prec UMINUS
    {$$ = ast_new_node(1, UMINUS, yylineno, $2);}
  | OP_NOT expr
    {$$ = ast_new_node(1, OP_NOT, yylineno, $2);}
  | OP_INC expr 
    {$$ = ast_new_node(1, OP_INC, yylineno, $2);}
  | expr OP_INC 
    {$$ = ast_new_node(1, OP_INC, yylineno, $1);}
  | OP_DEC expr 
    {$$ = ast_new_node(1, OP_DEC, yylineno, $2);}
  | expr OP_DEC 
    {$$ = ast_new_node(1, OP_DEC, yylineno, $1);}
  | IDENT '(' arg_list ')' {
      $$ = ast_new_node(1, FUNC_CALL, yylineno, $3);
      strcpy($$->value.str, $1);
    }
  | IDENT '(' ')' {
      $$ = ast_new_node(0, FUNC_CALL, yylineno);
      strcpy($$->value.str, $1);
    }
  | IDENT {
      $$=ast_new_node(0, IDENT, yylineno);
      strcpy($$->value.str, $1);
    }
  | L_INT {
      $$ = ast_new_node(0, L_INT, yylineno);
      $$->value.itg=$1;
    }
  | L_FLOAT {
      $$ = ast_new_node(0, L_FLOAT, yylineno);
      $$->value.flt=$1;
    }
  | L_STRING {
      $$ = ast_new_node(0, L_STRING, yylineno);
      strcpy($$->value.str, $1);
    }
  ;

arg_list: expr ',' arg_list 
    {$$ = ast_new_node(2, ARG_LIST, yylineno, $1, $3);}
  | expr {$$ = $1;}
  ;

%%

void yyerror(const char* fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  fprintf(stderr, "Grammar error (%d.%d): ", yylloc.first_line, yylloc.first_column);
  vfprintf(stderr, fmt, ap);
  fprintf(stderr, ".\n");
}