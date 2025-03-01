#include "../../inc/parser.h"

int	expecting = 0;

static void	read_squote(t_lexer *l)
{
	int	pos;
	
	read_char(l);
	if (l->ch == '\'') 
	{
		read_char(l);
		return ;
	}
	pos = l->position;
	while (pos < l->size)
	{
		if (l->input[pos] == '\'')
		{
			append_token(l, WORD, pos - l->position);
			read_char(l);
			break;
		}
		pos++;
	}
}

static void	read_dquote(t_lexer *l)
{
	int	pos;

	if (l->ch == '"') 
	{
		read_char(l);
		return ;
	}
	pos = l->position;
	while(pos < l->size)
	{
		if (l->input[pos] == '"')
		{
			if (pos > l->position)
				append_token(l, WORD, pos - l->position);
			read_char(l);
			break ;
		}
		else if (l->input[pos] == '$')
		{
			append_token(l, WORD, pos - l->position);
			lex_env_var(l);
			pos = l->position;
		}
		else
			pos++;
	}
}

int	lex_quote(t_lexer *l)
{
	if (l->ch == '\'')
		read_squote(l);
	else if (l->ch == '"')
	{
		read_char(l);
		read_dquote(l);
	}
	else
		return (0);
	return (1);
}
