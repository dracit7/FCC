
TESTS_SRC := \
	function.c\
	array.c\

TESTS := $(patsubst %.c, %, $(TESTS_SRC))

$(TESTS):
	@echo + $(EXECUTABLE)[TEST] Testing $@...
	@$(BINDIR)/$(EXECUTABLE) < $(TESTDIR)/$@.c

test: all $(TESTS)
	