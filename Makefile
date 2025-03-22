HDIR				=	inc
SDIR				=	src
ODIR				=	obj
LDIR				=	libft
TDIR				=	tests
NAME				=	minishell

#VPATH				=	$(SDIR):$(SDIR)/parser:$(SDIR)/exec

CC					?=	gcc
CFLAGS				?=	-g -Wall -Wextra -I$(HDIR)
MAKE_LIB			=	@make --no-print-directory -C
DIRS				=	$(sort $(dir $(OBJS)))
CFLAGS				+=	-Iast/ast.h -Ieva/eval.h -Iextra/extra.h -Ilexer/lexer.h
CRITERION_PATH		=	$(HDIR)/criterion
TEST_FLAGS			=	-I$(CRITERION_PATH)/include -L$(CRITERION_PATH)/lib

LIBFT_DIR			=	$(LDIR)/libft
LIBFT_FILE			=	libft.a
LIBFT				=	$(LIBFT_DIR)/$(LIBFT_FILE)
CFLAGS				+=	-I$(LIBFT_DIR)/include

SRCS				:=	$(shell find $(SDIR) -name "*.c")
OBJS				:=	$(patsubst $(SDIR)/%.c,$(ODIR)/%.o, $(SRCS))

TEST_OBJS			:=	$(filter-out $(ODIR)/main.o, $(OBJS))
TEST_SRCS			:=	$(wildcard $(TDIR)/*.c)
TEST_BINS			:=	$(patsubst $(TDIR)/%.c,$(TDIR)/bin/%, $(TEST_SRCS))

DEBUG_SRCS			:=	$(shell find ./debug -name "*.c")
DEBUG_OBJS			:=	$(patsubst debug/%.c,$(ODIR)/debug/%.o, $(DEBUG_SRCS))

export LD_LIBRARY_PATH=$(CRITERION_PATH)/lib:$LD_LIBRARY_PATH

all: $(LIBFT) $(NAME)

$(OBJS): $(ODIR)/%.o: $(SDIR)/%.c | $(DIRS)
	$(Q)$(CC) $(CFLAGS) -c -o $@ $<

$(ODIR)/debug/%.o: debug/%.c | $(DIRS)
	$(Q)$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): $(OBJS) $(LIBFT)
	$(Q)$(CC) $(CFLAGS) $^ -o $@ -lreadline

$(TDIR)/bin/%: $(TDIR)/%.c $(TEST_OBJS)
	$(Q)$(CC) $(CFLAGS) $(TEST_FLAGS) $^ $(LIBFT) -o $@ -lcriterion -lreadline
	$(Q)chmod +x $@

$(DIRS) $(TDIR)/bin:
	$(Q)mkdir -p $@

$(LIBFT):
	$(Q)$(MAKE_LIB) $(LIBFT_DIR)

t test: $(LIBFT) $(TDIR)/bin $(TEST_BINS)
	@for test in $(TEST_BINS) ; do \
		./$$test || exit 1 ; \
	done

c clean:
	$(Q)rm -rf $(ODIR)
	$(Q)rm -rf $(TDIR)/bin
	$(Q)$(MAKE_LIB) $(LIBFT_DIR) clean
	$(ECHO) "Clean is done!"

i init:
	@git submodule update --init --remote --recursive

f fclean: clean
	$(Q)rm -rf $(NAME)
	$(Q)$(MAKE_LIB) $(LIBFT_DIR) fclean

n norm:
	@-norminette $(SDIR)
	@echo
	@-norminette $(HDIR)/minishell.h

d debug: $(DEBUG_OBJS) $(TEST_OBJS) $(LIBFT)
	$(Q) $(CC) -g $(CFLAGS) $^ -o $@ -lreadline

re: fclean all

r run: $(NAME)
	@clear
	$(Q)./$(NAME)

.PHONY: all clean fclean re test n norm 

ifeq ($(V),2)
    Q =
    ECHO = @echo
else ifeq ($(V),1)
    Q = @
    ECHO = @echo
else
    Q = @
    ECHO = @:
endif

ifeq ($(F), 1)

else
	CFLAGS += -fsanitize=address
endif
