
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include <lib/ast.h>
#include <lib/lexer.h>
#include <lib/parser.h>
#include <lib/semantic.h>
#include <lib/log.h>

int yylex();
extern char* yytext;

char* input_file;
char* output_file;

int main(int argc, char* const argv[]) {
  int show_tuples = 0;

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
        show_tuples = 1;
        break;
    }

  // Specify input file.
	extern FILE *yyin;
  if (input_file && (yyin = fopen(input_file, "r")) == NULL)
    fault(-EOPEN, 0, input_file);

  // Print all tokens and exit.
  if (show_tuples) {
    int token;
    while ((token = yylex())) {
      printf("(%s, %s)\n", token_table[token], yytext);
    }
    return 0;
  }

  // Parse
	if (yyparse()) {}
	
  return 0;
}

