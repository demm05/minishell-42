#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

typedef enum e_tokentype
{
	ILLEGAL,	// When invalid input
	LPAREN,		// (
	RPAREN,		// )
	LBRACE,		// {
	RBRACE,		// }
	SQUOTE,		// '
	DQUOTE,		// "
	EOL,		// End of line
	PIPE,		// |
	LT,			// <
	GT,			// >
	DLT,		// <<
	DGT,		// >>
	CD,
	ECHO,
	PWD,
	EXPORT,		
	UNSET,
	ENV,
	EXIT,
	EXIT_STATUS,
}	t_token_type;

//typedef struct s_keywords
//{
//	const char		*key;
//	t_token_type	type;
//}	t_keywords;
//
//const t_keywords	g_keywords[] = {
//	{"echo", ECHO},
//	{"cd", CD},
//	{"pwd", PWD},
//	{"export", EXPORT},
//	{"unset", UNSET},
//	{"env", ENV},
//	{"exit", EXIT}
//};

typedef struct s_token
{
	t_token_type	type;
	char			*literal;
}	t_token;

typedef struct s_lexer {
	const char	*input;
	int			pos;
	int			read_postion;
	int			size;
	char		ch;
}	t_lexer;

t_lexer	*new_lexer(const char *str);
t_token *get_next_token(t_lexer *l);
t_lexer	*new_lexer(const char *str);
t_token	*new_token(t_token_type t, char *literal, bool duplicate_literal);
t_token *get_next_token(t_lexer *l);
void	read_char(t_lexer *l);

#endif
