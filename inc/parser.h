#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

typedef enum e_tokentype
{
	ILLEGAL,	// When invalid input
	EOL,		// End of line
	SQUOTE,		// '
	DQUOTE,		// "
	PIPE,		// |
	LT,			// <
	GT,			// >
	DLT,		// <<
	DGT,		// >>
	DSIGN,		// $
	RPATH,		// ./minishell
	ABSPATH,	// /bin
	CD,
	ECHO,
	PWD,
	EXPORT,		
	UNSET,
	ENV,
	EXIT,
	CLEAR,
	EXIT_STATUS,
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

t_lexer	*new_lexer(const char *str);
void	generate_tokens(t_lexer	*l);
int		lex_env_var(t_lexer *l);
int		lex_keyword(t_lexer *l);
int		append_token(t_lexer *l, t_token_type type, int size);
void	free_lexer(t_lexer *l);

t_token	*new_token(t_token_type t, t_lexer *l, int size);

// Lexer utils
void	read_char(t_lexer *l);
char	peek_char(t_lexer *l);
t_lexer	*new_lexer(const char *str);
bool	is_letter(char c);
void	eat_whitespaces(t_lexer *l);
bool	ft_isspace(char ch);
// Lexer utils

#endif
