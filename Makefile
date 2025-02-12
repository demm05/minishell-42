HDIR				=	inc
SDIR				=	src
ODIR				=	obj
LDIR				=	libft
TDIR				=	tests
NAME				=	minishell

#VPATH				=	$(SDIR):$(SDIR)/parser:$(SDIR)/exec

CC					?=	gcc
CFLAGS				?=	-g -Wall -Wextra -fsanitize=address -I$(HDIR)
MAKE_LIB			=	@make --no-print-directory -C
DIRS				=	$(sort $(dir $(OBJS)))

LIBFT_DIR			=	$(LDIR)/libft
LIBFT_FILE			=	libft.a
LIBFT				=	$(LIBFT_DIR)/$(LIBFT_FILE)
CFLAGS				+=	-I$(LIBFT_DIR)/include

SRCS				:=	$(shell find $(SDIR) -name "*.c")
OBJS				:=	$(patsubst $(SDIR)/%.c,$(ODIR)/%.o, $(SRCS))

TEST_OBJS			:=	$(filter-out $(ODIR)/main.o, $(OBJS))
TEST_SRCS			:=	$(wildcard $(TDIR)/*.c)
TEST_BINS			:=	$(patsubst $(TDIR)/%.c,$(TDIR)/bin/%, $(TEST_SRCS))

all: $(LIBFT) $(NAME)

$(OBJS): $(ODIR)/%.o: $(SDIR)/%.c | $(DIRS)
	$(Q)$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): $(OBJS) $(LIBFT)
	$(Q)$(CC) $(CFLAGS) $^ -o $@ -lreadline

$(TDIR)/bin/%: $(TDIR)/%.c $(TEST_OBJS)
	$(Q)$(CC) $(CFLAGS) $^ $(LIBFT) -o $@ -lcriterion
	$(Q)chmod +x $@

$(DIRS) $(TDIR)/bin:
	$(Q)mkdir -p $@

$(LIBFT):
	$(Q)$(MAKE_LIB) $(LIBFT_DIR)

t test: $(LIBFT) $(TDIR)/bin $(TEST_BINS)
	@for test in $(TEST_BINS) ; do \
		./$$test || exit 1 ; \
	done

clean:
	$(Q)rm -rf $(ODIR)
	$(Q)rm -rf $(TDIR)/bin
	$(Q)$(MAKE_LIB) $(LIBFT_DIR) clean
	$(ECHO) "Clean is done!"

fclean: clean
	$(Q)rm -rf $(NAME)
	$(Q)$(MAKE_LIB) $(LIBFT_DIR) fclean

n norm:
	@-norminette $(SDIR)
	@echo
	@-norminette $(HDIR)

re: fclean all

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
