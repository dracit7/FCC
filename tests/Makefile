
TESTS_SRC := \
	function.c\
	array.c\
	struct.c\
	literal.c\
	operators.c\
	comment.c\
	control.c\
	semantics.c\

TESTS := $(patsubst %.c, test-%, $(TESTS_SRC))

$(TESTS): all
	@echo + $(EXECUTABLE)[TEST] $@
	@(\
		if $(BINDIR)/$(EXECUTABLE) -o tmp/$@.ll -f $(patsubst test-%, $(TESTDIR)/%.c, $@);\
		then echo + $(EXECUTABLE)[TEST] $@ passed.;\
		else echo + $(EXECUTABLE)[TEST] $@ failed.; fi;\
	)
	@llvm-as tmp/$@.ll -o tmp/$@.bc
	@clang -Wno-all -emit-llvm -S $(patsubst test-%, $(TESTDIR)/%.c, $@) -o tmp/$@.bc
	@llc -relocation-model=pic tmp/$@.bc
	@gcc tmp/$@.s -o tmp/$@

test: $(TESTS)
	