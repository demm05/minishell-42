#ifndef PTYPES_H
# define PTYPES_H

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

typedef struct s_lexer
{
	const char	*input;
	t_token		*tokens;
	// current position in input (points to current char)
	int			position;
	// current reading position in input (after current char)
	int			read_postion;
	// lenght of input
	int			size;
	// current char under examination(poistiob)
	char		ch;
}	t_lexer;

typedef struct s_astnode
{
	struct s_astnode	*next;
	struct s_astnode	*prev;
	struct s_astnode	*children;
	const char			*literal;
	int					lit_size;
	int					childs;
	t_token_type		type;
}	t_astnode;

#endif
