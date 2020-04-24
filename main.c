
#include <stdio.h>
#include <stdlib.h>

#include <lib/ast.h>
#include <lib/parser.h>

int main(int argc, const char *args[]) {
  // yydebug = 1;

	extern FILE *yyin;
	if(argc > 1 && (yyin = fopen(args[1], "r")) == NULL) {
		fprintf(stderr, "can not open %s\n", args[1]);
		exit(1);
	}
	if(yyparse()) {
		exit(-1);
	}
	
  return 0;
}

