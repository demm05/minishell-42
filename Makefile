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

LIBFT_DIR			=	$(LDIR)/libft
LIBFT_FILE			=	libft.a
LIBFT				=	$(LIBFT_DIR)/$(LIBFT_FILE)
CFLAGS				+=	-I$(LIBFT_DIR)/include

SRCS				:=	$(shell find $(SDIR) -name "*.c")
OBJS				:=	$(patsubst $(SDIR)/%.c,$(ODIR)/%.o, $(SRCS))

all: $(LIBFT) $(NAME)

$(OBJS): $(ODIR)/%.o: $(SDIR)/%.c | $(DIRS)
	$(Q)$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): $(OBJS) $(LIBFT)
	$(Q)$(CC) $(CFLAGS) $^ -o $@ -lreadline

$(DIRS):
	$(Q)mkdir -p $@

$(LIBFT):
	$(Q)$(MAKE_LIB) $(LIBFT_DIR)

compiledb:
	@compiledb make -n all > /dev/null 2>&1

v valgrind: all
	valgrind --suppressions=inc/rl.supp --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes ./$(NAME)

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
