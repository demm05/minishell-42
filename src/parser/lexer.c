#include "../../inc/parser.h"
#include "../../inc/minishell.h"
#include "libft.h"
#include <stdlib.h>

//static inline t_token *get_single_ch_token(t_lexer *l);
//static inline t_token *get_multi_ch_token(t_lexer *l);
//static inline t_token *get_keyword_token(t_lexer *l);
//
t_token *get_next_token(t_lexer *l)
{
	t_token	*tok;

	eat_whitespaces(l);
	
	if (!l->ch)
		tok = new_token(EOL, l, 0);
	else if ((tok = lex_env_var(l)))
		;
	else if ((tok = lex_keyword(l)))
		;
	else
		tok = new_token(ILLEGAL, l, 1);
	return (tok);
}

t_token	*new_token(t_token_type t, t_lexer *l, int size)
{
	t_token	*tok;

	if (!l)
		return (NULL);
	tok = malloc(sizeof(t_token));
	if (!tok)
		return (NULL);
	tok->type = t;
	tok->size = size;
	tok->literal = l->input + l->position;
	if (size > 0)
	{
		l->read_postion += size - 1;
		read_char(l);
	}
	return (tok);
}

//static inline t_token *get_keyword_token(t_lexer *l)
//{
//	return (NULL);
//}
//
//static inline t_token *get_single_ch_token(t_lexer *l)
//{
//	if (l->ch == 0)
//		return (new_token(EOL, "", 0));
//	else if (l->ch == '\'')
//		return (new_token(SQUOTE, "'", 0));
//	else if (l->ch == '\"')
//		return (new_token(DQUOTE, "\"", 0));
//	else if (l->ch == '|')
//		return (new_token(PIPE, "|", 0));
//	else if (l->ch == '$')
//		return (new_token(DSIGN, "$", 0));
//	return (NULL);
//}
//
//static inline t_token *get_multi_ch_token(t_lexer *l)
//{
//	if (l->ch == '<')
//	{
//		if (peek_char(l) == '<')
//		{
//			read_char(l);
//			return (new_token(DLT, "<<", 0));
//		}
//		else
//			return (new_token(LT, "<", 0));
//	}
//	else if (l->ch == '>')
//	{
//		if (peek_char(l) == '>')
//		{
//			read_char(l);
//			return (new_token(DGT, ">>", 0));
//		}
//		else
//			return (new_token(GT, ">", 0));
//	}
//	return (NULL);
//}
