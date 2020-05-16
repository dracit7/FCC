
## FCC

FCC is the compiler for a C-like language **FanC**. This language implements a subset of C's functionalities and supports several special features. It is developed as the course design of the compiler's principles course in HUST.

### Dependencies

FCC leverages `flex` and `bison` to implement its lexer and parser. Please ensure that they're installed on your system.

FCC's backend is implemented with the help of [LLVM](https://llvm.org/)'s interfaces in C, so LLVM is also required for compiling this project.

### Usage

### Testing

Execute `make test` to run all tests, or `make test-xxx` to run a specific test, where `xxx` is the name of the test case.

All test cases are placed under `tests/`. To add new test cases, put the source file in `tests/` and edit `tests/Makefile`, add the source file to `TESTS_SRC`.

When testing, following command line arguments could be used:

- `SHOW_TUPLES=1`: show lex tuples.
- `SHOW_AST=1`: show the abstract syntax tree.
- `SHOW_STAB=1`: show the symbol table in each scope.
- `SHOW_IR=1`: show the IR code.

Compiled test binaries would be placed in `tmp` and could be straightly executed to verify the correctness of FCC.