
lexer: $(SCRIPTS)/lexer.l
	@echo + $(LEX)[SCRIPTS] $<
	@$(LEX) -o $(LIBDIR)/lexer.c $<

parser: $(SCRIPTS)/parser.y
	@echo + $(YACC)[SCRIPTS] $<
	@$(YACC) --defines=$(LIBDIR)/parser.h -o $(LIBDIR)/parser.c -r itemset --report-file=$(OBJDIR)/parser.table --warnings=none $<

all: lexer parser