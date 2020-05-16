
BINDIR := bin
LIBDIR := lib
OBJDIR := obj
TESTDIR := tests
SCRIPTS := scripts

CC := gcc
LEX := flex
YACC := bison

CFLAGS := \
	-I.\
	`llvm-config --cflags --ldflags --libs`\

EXECUTABLE := fcc

ifdef SHOW_AST
CFLAGS += -DSHOW_AST
endif

ifdef SHOW_TUPLES
BINFLAGS += -l
endif

ifdef SHOW_STAB
CFLAGS += -DSHOW_STAB
endif

ifdef SHOW_IR
CFLAGS += -DSHOW_IR
endif

.PHONY: all lexer parser

all: setup
	@echo + cc[MAIN] main.c
	@$(CC) $(CFLAGS) -o $(BINDIR)/$(EXECUTABLE) main.c $(LIB_OBJ)

include scripts/Makefile
include lib/Makefile
include tests/Makefile

setup:
	@mkdir -p bin
	@mkdir -p obj
	@mkdir -p tmp

install: all
	@sudo mv bin/fcc /usr/bin/fcc

uninstall:
	@sudo rm -f /usr/bin/fcc

clean:
	rm -rf bin
	rm -rf obj
	rm -rf tmp