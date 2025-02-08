HDIR				=	inc
SDIR				=	src
ODIR				=	obj
LDIR				=	libft
BIN					=	minishell

#VPATH				=	$(SDIR):$(SDIR)/parser:$(SDIR)/exec

CC					=	gcc
CFLAGS				=	-Wall -Wextra -Werror -I$(HDIR)
MAKE_LIB			=	@make --no-print-directory -C

LIBFT_DIR			=	$(LDIR)/libft
LIBFT_FILE			=	libft.a
LIBFT				=	$(LIBFT_DIR)/$(LIBFT_FILE)
CFLAGS				+=	-I$(LIBFT_DIR)/include

CRCS				:=	$(shell find $(SDIR) -name "*.c")
OBJS				:=	$(patsubst $(SDIR)/%.c, $(ODIR)/%.o, $(SRCS))

$(info	SRCS is $(SRCS))

all: $(BIN)

$(ODIR)/%.o: $(SDIR)/%.c | $(ODIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(BIN): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $^ -o $@

$(ODIR):
	@mkdir -p $@

$(LIBFT):
	$(MAKE_LIB) $(LIBFT_DIR)

lib_clean:
	$(MAKE_LIB) $(LIBFT_DIR) clean

lib_fclean:
	$(MAKE_LIB) $(LIBFT_DIR) fclean

lib_re:
	$(MAKE_LIB) $(LIBFT_DIR) re
	
clean: lib_clean
	@rm -rf $(ODIR)

fclean: clean lib_fclean
	@rm -rf $(PUSH_SWAP) $(CHECKER)

re: lib_re all

.PHONY: all lib_fclean lib_clean clean fclean
