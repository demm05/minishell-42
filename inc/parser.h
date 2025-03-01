#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

typedef enum e_tokentype
{
	LT,			// <
	GT,			// >
	DLT,		// <<
	DGT,		// >>
	DSIGN,		// $
	RPATH,		// ./minishell
	ABSPATH,	// /bin
	SQUOTE,		// '
	DQUOTE,		// "

	// Better names
	EOL,		// End of line
	ILLEGAL,	// When invalid input
	EXIT_STATUS,// $?
	AND,		// &&
	OR,			// ||
	REDIR_OUT,	// >
	REDIR_IN,	// <
	REDIR_OUT_A,// >>
	HERE_DOC,	// <<	
	PIPE,		// |
	EXPAND_VAR,	// $ better
	VAR_EXP,	// $
	EXEC,		// Executable like ls wc grep 
	WORD,		// It could be an argument or file
	PATH,		// Can be relative or absolute eg ./ or /
	
	// Built in shell exec
	CD,
	ECHO,
	PWD,
	EXPORT,		
	UNSET,
	ENV,
	EXIT,
}	t_token_type;

typedef struct s_keyword
{
	const char		*key;
	t_token_type	type;
	int				size;
}	t_keyword;

typedef struct s_token
{
	struct s_token	*next;
	struct s_token	*prev;
	const char		*literal;
	t_token_type	type;
	int				size;
}	t_token;

typedef struct s_lexer {
	const char	*input;
	t_token		*tokens;
	int			position;  // current position in input (points to current char)
	int			read_postion; // current reading position in input (after current char)
	int			size;
	char		ch; // current char under examination
}	t_lexer;

typedef struct s_astnode
{
	struct s_astnode	**children;
	const char			*literal;
	int					lit_size;
	int					childs;
	t_token_type		type;
}	t_astnode;

void		generate_tokens(t_lexer	*l);
void		free_lexer(t_lexer *l);
void		read_char(t_lexer *l);
void		eat_whitespaces(t_lexer *l);
void		add_child(t_astnode *parent, t_astnode *child);
void		print_ast(t_astnode *node, int depth);
void		free_ast(t_astnode **node);
int			lex_env_var(t_lexer *l);
int			lex_keyword(t_lexer *l);
int			lex_executable(t_lexer *l);
int			lex_word(t_lexer *l);
int			is_there_exec(t_lexer *l);
int			append_token(t_lexer *l, t_token_type type, int size);
int			analyze_tokens(t_lexer *l);
int			get_pos_next_whitespace(t_lexer *l);
char		peek_char(t_lexer *l);
char		*decode(t_token_type t);
t_lexer		*new_lexer(const char *str);
t_lexer		*new_lexer(const char *str);
t_token		*new_token(t_token_type t, t_lexer *l, int size);
t_astnode	*new_astnode(t_token *tok);
t_astnode	*parse_exec(t_token **token);
t_astnode	*parse(t_lexer *l);
bool		is_letter(char c);
bool		ft_isspace(char ch);
bool		is_token_exec(t_token_type t);
bool		match(t_token *token, t_token_type expected[], int size);

#endif
