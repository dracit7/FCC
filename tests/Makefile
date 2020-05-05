
TESTS_SRC := \
	function.c\
	array.c\
	struct.c\
	literal.c\
	operators.c\
	comment.c\
	control.c\

TESTS := $(patsubst %.c, test-%, $(TESTS_SRC))

$(TESTS): all
	@echo + $(EXECUTABLE)[TEST] $@
	@(\
		if $(BINDIR)/$(EXECUTABLE) $(BINFLAGS) -f $(patsubst test-%, $(TESTDIR)/%.c, $@);\
		then echo + $(EXECUTABLE)[TEST] $@ passed.;\
		else echo + $(EXECUTABLE)[TEST] $@ failed.; fi;\
	)

test: $(TESTS)
	