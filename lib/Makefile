
LIB_SRC := \
	lexer.c\
	parser.c\
	ast.c\
	log.c\

LIB_OBJ := $(patsubst %.c, $(OBJDIR)/%.o, $(LIB_SRC))
LIB_INC := $(patsubst %.c, $(LIBDIR)/%.h, $(LIB_SRC))

$(OBJDIR)/%.o: $(LIBDIR)/%.c $(LIB_INC)
	@echo + cc[LIB] $<
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c -o $@ $<

all: $(LIB_OBJ)