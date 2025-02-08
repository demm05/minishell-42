HDIR				=	inc
SDIR				=	src
ODIR				=	obj
LDIR				=	libft
BIN					=	minishell

#VPATH				=	$(SDIR):$(SDIR)/parser:$(SDIR)/exec

CC					=	gcc
CFLAGS				=	-Wall -Wextra -I$(HDIR)
MAKE_LIB			=	@make --no-print-directory -C

LIBFT_DIR			=	$(LDIR)/libft
LIBFT_FILE			=	libft.a
LIBFT				=	$(LIBFT_DIR)/$(LIBFT_FILE)
CFLAGS				+=	-I$(LIBFT_DIR)/include

SRCS				:=	$(shell find $(SDIR) -name "*.c")
OBJS				:=	$(patsubst $(SDIR)/%.c, $(ODIR)/%.o, $(SRCS))
DIRS				=	$(sort $(dir $(OBJS)))

all: $(LIBFT) $(BIN)

$(ODIR)/%.o: $(SDIR)/%.c | $(DIRS)
	$(CC) $(CFLAGS) -c -o $@ $<

$(BIN): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $^ -o $@

$(DIRS):
	@mkdir -p $@

$(LIBFT):
	$(MAKE_LIB) $(LIBFT_DIR)
	
clean:
	$(MAKE_LIB) $(LIBFT_DIR) clean
	@rm -rf $(ODIR)

fclean: clean lib_fclean
	@rm -rf $(BIN)
	$(MAKE_LIB) $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all lib_fclean lib_clean clean fclean
