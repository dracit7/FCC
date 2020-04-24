
BINDIR := bin
LIBDIR := lib
OBJDIR := obj
SCRIPTS := scripts

CC := gcc
LEX := flex
YACC := bison

CFLAGS := \
	-I.\
	-DSHOW_AST\

.PHONY: all lexer parser

all: setup
	@echo + cc[MAIN] main.c
	@$(CC) $(CFLAGS) -o bin/main main.c $(LIB_OBJ)

include scripts/Makefile
include lib/Makefile

setup:
	@mkdir -p bin
	@mkdir -p obj


clean:
	rm -rf bin
	rm -rf obj