
TESTS_SRC := \
	function.c\
	array.c\
	struct.c\
	literal.c\
	operators.c\
	comment.c\
	control.c\
	semantics.c\
	fibonacci.c\

TESTS := $(patsubst %.c, test-%, $(TESTS_SRC))

ifndef USE_CLANG

$(TESTS): all
	@echo + $(EXECUTABLE)[TEST] $@
	@(\
		if $(BINDIR)/$(EXECUTABLE) -o tmp/$@.ll -f $(patsubst test-%, $(TESTDIR)/%.c, $@);\
		then echo + $(EXECUTABLE)[TEST] $@ passed.;\
		else echo + $(EXECUTABLE)[TEST] $@ failed.; fi;\
	)
	@llc -relocation-model=pic tmp/$@.ll
	@gcc tmp/$@.s -o tmp/$@

else

$(TESTS): all
	@echo + $(EXECUTABLE)[TEST] $@
	@(\
		if clang -Wno-all -emit-llvm -S $(patsubst test-%, $(TESTDIR)/%.c, $@) -o tmp/$@.ll;\
		then echo + $(EXECUTABLE)[TEST] $@ passed.;\
		else echo + $(EXECUTABLE)[TEST] $@ failed.; fi;\
	)
	@llc -relocation-model=pic tmp/$@.ll
	@gcc tmp/$@.s -o tmp/$@

endif

test: $(TESTS)
	