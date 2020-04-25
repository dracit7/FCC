
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include <lib/ast.h>
#include <lib/lexer.h>
#include <lib/parser.h>
#include <lib/log.h>

int yylex();
extern char* yytext;

int main(int argc, char* const argv[]) {
  char* input_file = NULL;
  char* output_file = NULL;
  int lex_only = 0;

  // Handle command line arguments.
  char opt;
  while ((opt = getopt(argc, argv, "df:o:l")) != -1)
    switch (opt) {
      case 'f':
        input_file = optarg;
        break;
      case 'd':
        yydebug = 1;
        break;
      case 'o':
        output_file = optarg;
        break;
      case 'l':
        lex_only = 1;
        break;
    }

  // Specify input file.
	extern FILE *yyin;
  if (input_file && (yyin = fopen(input_file, "r")) == NULL)
    fault("Can not open %s.", input_file);

  // Specify output file.
  if (output_file && (freopen(output_file, "w", stdout)) == NULL) 
    fault("Can not open %s.", output_file);
  
  // Print all tokens and exit.
  if (lex_only) {
    int token;
    while ((token = yylex())) {
      printf("(%s, %s)\n", token_table[token], yytext);
    }
    return 0;
  }

  // Parse
	if (yyparse()) {
    fault("yyparse() returned an error.", 0);
	}
	
  return 0;
}

