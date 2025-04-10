HDIR				=	inc
SDIR				=	src
ODIR				=	obj
LDIR				=	libft
TDIR				=	tests
NAME				=	minishell

CC					=	gcc
CFLAGS				=	-g -Werror -Wall -Wextra -I$(HDIR)
MAKE_LIB			=	@make --no-print-directory -C
DIRS				=	$(sort $(dir $(OBJS)))

LIBFT_FILE			=	libft.a
LIBFT				=	$(LDIR)/$(LIBFT_FILE)
CFLAGS				+=	-I$(LDIR)/include

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
	$(Q)$(MAKE_LIB) $(LDIR)

compiledb:
	@compiledb make -n all > /dev/null 2>&1

v valgrind: all inc/rl.supp
	valgrind --suppressions=inc/rl.supp --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes ./$(NAME)

c clean:
	$(Q)rm -rf $(ODIR)
	$(Q)rm -rf $(TDIR)/bin
	$(Q)$(MAKE_LIB) $(LDIR) clean
	$(ECHO) "Clean is done!"

i init:
	@git submodule update --init --remote --recursive

f fclean: clean
	$(Q)rm -rf $(NAME)
	$(Q)$(MAKE_LIB) $(LDIR) fclean

n norm:
	@-norminette $(SDIR)
	@echo
	@-norminette $(HDIR)/minishell.h

re: fclean all

r run: $(NAME)
	@clear
	$(Q)./$(NAME)

inc/rl.supp:
	@echo "{\nreadline_all\nMemcheck:Leak\n...\nobj:*/libreadline.so*\n}" > $@

.PHONY: all clean fclean re test n norm v r

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
