
%debug
%locations

%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <inc/ds.h>

#include <lib/ast.h>
#include <lib/semantic.h>
#include <lib/llvm.h>

extern int yylineno;
extern char* input_file;
extern char* output_file;

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
%token T_STRUCT
%token T_VOID

// Operators
// 
// Operators that're declared latter has
// higher priority.
%left ASSIGN COMP_ASSIGN
%token <str> COMP_ASSIGN
%left OP_OR
%left OP_AND
%left OP_EQ OP_NEQ
%left OP_G OP_L OP_GE OP_LE 
%left OP_ADD OP_SUB
%left OP_STAR OP_DIV OP_MOD
%right OP_NOT OP_INC OP_DEC UMINUS
%left OP_DOT

// Keywords for control
%token IF
%token ELSE
%token RETURN
%token WHILE
%token FOR
%token BREAK
%token CONTINUE

// Identifiers
%token <str> IDENT

// Literals
%token <integer> L_INT
%token <integer> L_CHAR
%token <floatpoint> L_FLOAT
%token <str> L_STRING

// Some node types
%token EXT_DEF_LIST EXT_VAR_DEF FUNC_DEF
  EXT_DECL_LIST FUNC_DECL PARAM_LIST PARAM_DEC
  STMT_LIST IF_THEN IF_THEN_ELSE VAR_DEF
  DEC_LIST FUNC_CALL ARG_LIST ARRAY_CALL
  VAR_INIT MEMBER_LIST STRUCT_DEF MEMBER_CALL
  CODE_BLOCK

// Precedence for resolving the ambiguity
// between if-else and if
%nonassoc NO_ELSE

// Nonterminals
%type <node> program ext_def_list ext_def
  var_type ext_decl_list var_name func_decl
  param_list param code_block stmt_list stmt
  decl decl_list var_decl expr arg_list type_void
  member_list left_value

%start program

%%

program: ext_def_list {
    ast_display($1, 1);
    semantic_analysis($1);
    generate_IR($1, input_file, output_file);
  }
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
  | T_STRUCT IDENT '{' member_list '}' ';' {
      $$ = ast_new_node(1, STRUCT_DEF, yylineno, $4);
      strcpy($$->value.str, $2);
    }
  ;

type_void: T_VOID
    {$$ = ast_new_node(0, T_VOID, yylineno);}
  ;

var_type: T_INT
    {$$ = ast_new_node(0, T_INT, yylineno);}
  | T_FLOAT {$$ = ast_new_node(0, T_FLOAT, yylineno);}
  | T_CHAR {$$ = ast_new_node(0, T_CHAR, yylineno);}
  | T_STRING {$$ = ast_new_node(0, T_STRING, yylineno);}
  | T_STRUCT IDENT '{' member_list '}' {
      $$ = ast_new_node(1, T_STRUCT, yylineno, $4);
      strcpy($$->value.str, $2);
    }
  | T_STRUCT '{' member_list '}' 
    {$$ = ast_new_node(1, T_STRUCT, yylineno, $3);}
  | T_STRUCT IDENT {
      $$ = ast_new_node(0, T_STRUCT, yylineno);
      strcpy($$->value.str, $2);
    }
  ;

member_list: var_type decl_list ';' member_list
    {$$ = ast_new_node(3, MEMBER_LIST, yylineno, $1, $2, $4);}
  | {$$ = NULL;}
  ;

ext_decl_list: var_decl {$$ = $1;}
  | var_decl ',' ext_decl_list
    {$$ = ast_new_node(2, EXT_DECL_LIST, yylineno, $1, $3);}
  ;  

var_name: IDENT {
    $$ = ast_new_node(0, IDENT, yylineno);
    strcpy($$->value.str, $1);
  }
  | var_name '[' ']' {
    $$ = $1;
    $$->capacity[$$->dim++] = 0;
  }
  | var_name '[' L_INT ']' {
    $$ = $1;
    $$->capacity[$$->dim++] = $3;
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
    {$$ = ast_new_node(1, CODE_BLOCK, yylineno, $2);}
  ;

stmt_list: {$$ = NULL;}  
  | stmt stmt_list {$$ = ast_new_node(2, STMT_LIST, yylineno, $1, $2);}
  | decl stmt_list {$$ = ast_new_node(2, STMT_LIST, yylineno, $1, $2);}
  ;

stmt: expr ';' 
    {$$ = $1;}
  | code_block
    {$$ = $1;}
  | RETURN ';'
    {$$ = ast_new_node(0, RETURN, yylineno);}
  | RETURN expr ';'
    {$$ = ast_new_node(1, RETURN, yylineno, $2);}
  | IF '(' expr ')' stmt %prec NO_ELSE
    {$$ = ast_new_node(2, IF_THEN, yylineno, $3, $5);}
  | IF '(' expr ')' stmt ELSE stmt 
    {$$ = ast_new_node(3, IF_THEN_ELSE, yylineno, $3, $5, $7);}
  | WHILE '(' expr ')' stmt
    {$$ = ast_new_node(2, WHILE, yylineno, $3, $5);}
  | FOR '(' stmt expr ';' expr ')' stmt
    {$$ = ast_new_node(4, FOR, yylineno, $3, $4, $6, $8);}
  | FOR '(' decl expr ';' expr ')' stmt
    {$$ = ast_new_node(4, FOR, yylineno, $3, $4, $6, $8);}
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
    {$$ = ast_new_node(2, VAR_INIT, yylineno, $1, $3);}
  ;

expr: left_value ASSIGN expr {
    $$ = ast_new_node(2, ASSIGN, yylineno, $1, $3);
  }
  | left_value COMP_ASSIGN expr {
    $$ = ast_new_node(2, COMP_ASSIGN, yylineno, $1, $3);
    strcpy($$->value.str, $2);
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
  | expr OP_LE expr
    {$$ = ast_new_node(2, OP_LE, yylineno, $1, $3);}
  | expr OP_GE expr
    {$$ = ast_new_node(2, OP_GE, yylineno, $1, $3);}
  | expr OP_L expr
    {$$ = ast_new_node(2, OP_L, yylineno, $1, $3);}
  | expr OP_G expr
    {$$ = ast_new_node(2, OP_G, yylineno, $1, $3);}
  | expr OP_NEQ expr
    {$$ = ast_new_node(2, OP_NEQ, yylineno, $1, $3);}
  | expr OP_EQ expr
    {$$ = ast_new_node(2, OP_EQ, yylineno, $1, $3);}
  | '(' expr ')' 
    {$$ = $2;}
  | OP_SUB expr %prec UMINUS
    {$$ = ast_new_node(1, UMINUS, yylineno, $2);}
  | OP_NOT expr
    {$$ = ast_new_node(1, OP_NOT, yylineno, $2);}
  | OP_INC expr 
    {$$ = ast_new_node(1, OP_INC, yylineno, $2);}
  | left_value OP_INC 
    {$$ = ast_new_node(1, OP_INC, yylineno, $1);}
  | OP_DEC expr 
    {$$ = ast_new_node(1, OP_DEC, yylineno, $2);}
  | left_value OP_DEC 
    {$$ = ast_new_node(1, OP_DEC, yylineno, $1);}
  | expr OP_DOT IDENT {
      $$ = ast_new_node(1, MEMBER_CALL, yylineno, $1);
      strcpy($$->value.str, $3);
    }
  | IDENT '(' arg_list ')' {
      $$ = ast_new_node(1, FUNC_CALL, yylineno, $3);
      strcpy($$->value.str, $1);
    }
  | IDENT '(' ')' {
      $$ = ast_new_node(0, FUNC_CALL, yylineno);
      strcpy($$->value.str, $1);
    }
  | IDENT {
      $$ = ast_new_node(0, IDENT, yylineno);
      strcpy($$->value.str, $1);
    }
  | expr '[' expr ']' {
      $$ = ast_new_node(2, ARRAY_CALL, yylineno, $1, $3);
    }
  | L_INT {
      $$ = ast_new_node(0, L_INT, yylineno);
      $$->value.itg=$1;
    }
  | L_CHAR {
      $$ = ast_new_node(0, L_CHAR, yylineno);
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

left_value: IDENT {
      $$ = ast_new_node(0, IDENT, yylineno);
      strcpy($$->value.str, $1);
    }
  | expr OP_DOT IDENT {
      $$ = ast_new_node(1, MEMBER_CALL, yylineno, $1);
      strcpy($$->value.str, $3);
    }
  | expr '[' expr ']' {
      $$ = ast_new_node(2, ARRAY_CALL, yylineno, $1, $3);
    }
  ;

arg_list: expr ',' arg_list 
    {$$ = ast_new_node(2, ARG_LIST, yylineno, $1, $3);}
  | expr {$$ = ast_new_node(2, ARG_LIST, yylineno, $1, 0);}
  ;

%%

void yyerror(const char* fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  fprintf(stderr, "Grammar error (%d.%d): ", yylloc.first_line, yylloc.first_column);
  vfprintf(stderr, fmt, ap);
  fprintf(stderr, ".\n");
}