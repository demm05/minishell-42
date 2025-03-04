#include "../../inc/parser.h"

static void	read_squote(t_lexer *l)
{
	int	pos;

	pos = l->position;
	while (pos < l->size && l->input[pos] != '\'')
		pos++;

	if (l->input[pos] == '\'')
	{
		append_token(l, WORD, pos - l->position);
		read_char(l);
	}
	else
		append_token(l, ILLEGAL, pos - --l->position);
}

static void	read_dquote(t_lexer *l)
{
	int	pos;

	pos = l->position;
	while (pos < l->size)
	{
		if (l->ch == '\\')
		{
			append_token(l, WORD, pos - l->position - 1);
			read_char(l);
			pos = l->position;
		}
		else if (l->input[pos] == '"')
			break ;
		else if (l->input[pos] == '$')
		{
			append_token(l, WORD, pos - l->position);
			lex_env_var(l);
			pos = l->position;
		}
		else
			pos++;
	}
	if (l->input[pos] == '"')
	{
		if (pos > l->position)
			append_token(l, WORD, pos - l->position);
		read_char(l);
	}
	else
		append_token(l, ILLEGAL, pos - --l->position);
}

int	lex_quote(t_lexer *l)
{
	if (l->ch != '\'' && l->ch != '"')
		return (0);
	// TODO: add token as quote so exec could enter heredoc when quote is missing
	if (l->ch == '\'')
	{
		read_char(l);
		if (l->ch == '\'')
			read_char(l);
		else
			read_squote(l);
	}
	else if (l->ch == '"')
	{
		read_char(l);
		if (l->ch == '"')
			read_char(l);
		else
			read_dquote(l);
	}
	return (1);
}
