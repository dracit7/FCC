
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

EXECUTABLE := main

ifdef SHOW_AST
CFLAGS += -DSHOW_AST
endif

ifdef SHOW_TUPLES
BINFLAGS += -l
endif

ifdef SHOW_STAB
CFLAGS += -DSHOW_STAB
endif

ifndef SHOW_IR
BINFLAGS += -o tmp/$@.bc
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

clean:
	rm -rf bin
	rm -rf obj
	rm -rf tmp