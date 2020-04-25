
lexer: $(SCRIPTS)/lexer.l
	@echo + $(LEX)[SCRIPTS] $<
	@$(LEX) -o $(LIBDIR)/lexer.c $<

parser: $(SCRIPTS)/parser.y
	@echo + $(YACC)[SCRIPTS] $<
	@$(YACC) --defines=$(LIBDIR)/parser.h -o $(LIBDIR)/parser.c --warnings=none $<

all: lexer parser