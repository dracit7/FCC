
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
	@$(BINDIR)/$(EXECUTABLE) $(BINFLAGS) -f $(patsubst test-%, $(TESTDIR)/%.c, $@)

test: $(TESTS)
	