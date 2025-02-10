#include "../../inc/parser.h"
#include "../../inc/minishell.h"
#include "libft.h"
#include <stdlib.h>

void	read_char(t_lexer *l)
{
	if (l->read_postion >= l->size) 
		l->ch = 0;
	else
		l->ch = l->input[l->read_postion];
	l->pos = l->read_postion;
	l->read_postion += 1;
}

char	peek_char(t_lexer *l)
{
	if (l->read_postion >= l->size)
		return (0);
	return (l->input[l->read_postion]);
}

t_lexer	*new_lexer(const char *str)
{
	t_lexer	*l;

	if (!str)
		return (NULL);
	l = malloc(sizeof(t_lexer));
	if (!l)
		return (NULL);
	ft_memset(l, 0, sizeof(t_lexer));
	l->input = str;
	l->size = ft_strlen(str);
	read_char(l);
	return (l);
}

t_token	*new_token(t_token_type t, char *literal, bool duplicate_literal)
{
	t_token	*tok;

	tok = malloc(sizeof(t_token));
	if (!tok)
		return (NULL);
	tok->type = t;
	if (duplicate_literal && literal)
		tok->literal = ft_strdup(literal);
	else
		tok->literal = literal;
	return (tok);
}

bool	is_letter(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

void	eat_whitespaces(t_lexer *l)
{
	while (l->ch == ' ' || l->ch == '\t' || l->ch == '\r')
		read_char(l);
}

t_token *get_next_token(t_lexer *l)
{
	t_token	*tok;

	eat_whitespaces(l);

	if (l->ch == 0)
		tok = new_token(EOL, "", 0);
	else if (l->ch == '{')
		tok = new_token(LBRACE, "{", 0);
	else if (l->ch == '}')
		tok = new_token(RBRACE, "}", 0);
	else if (l->ch == '(')
		tok = new_token(LPAREN, "(", 0);
	else if (l->ch == ')')
		tok = new_token(RPAREN, ")", 0);
	else if (l->ch == '\'')
		tok = new_token(SQUOTE, "'", 0);
	else if (l->ch == '\"')
		tok = new_token(DQUOTE, "\"", 0);
	else if (l->ch == '|')
		tok = new_token(PIPE, "|", 0);
	else if (l->ch == '<')
	{
		if (peek_char(l) == '<')
		{
			read_char(l);
			tok = new_token(DLT, "<<", 0);
		}
		else
			tok = new_token(LT, "<", 0);
	}
	else if (l->ch == '>')
	{
		if (peek_char(l) == '>')
		{
			read_char(l);
			tok = new_token(DGT, ">>", 0);
		}
		else
			tok = new_token(GT, ">", 0);
	}
	else
		tok = new_token(ILLEGAL, &l->ch, 0);
	read_char(l);
	return (tok);
}
