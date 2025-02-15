#include "../../inc/parser.h"
#include "../../inc/minishell.h"
#include <stdlib.h>

void	generate_tokens(t_lexer	*l)
{
	while (l->position < l->size - 1)
	{
		eat_whitespaces(l);
		if (l->ch == '$')
			lex_env_var(l);
		//else if (l->ch == '<' || l->ch == '>')
		//	;
		else if (lex_keyword(l))
			;
		else
			append_token(l, ILLEGAL, 1);
	}
	append_token(l, EOL, 0);
}

// On completion this func will return 0 if the node 
// was added to the list of tokens otherwise 1
int	append_token(t_lexer *l, t_token_type type, int size)
{
	t_token	*new;

	if (!l || size < 0)
		return (1);
	new = new_token(type, l, size);
	if (!new)
		return (1);
	if (!l->tokens)
	{
		new->prev = new;
		l->tokens = new;
		return (0);
	}
	else
		new->prev = l->tokens;
	l->tokens->prev->next = new;
	l->tokens->prev = new;
	return (0);
}

t_token	*new_token(t_token_type type, t_lexer *l, int size)
{
	t_token	*tok;

	if (!l)
		return (NULL);
	tok = malloc(sizeof(t_token));
	if (!tok)
		return (NULL);
	tok->type = type;
	tok->size = size;
	tok->literal = l->input + l->position;
	tok->next = NULL;
	tok->prev = NULL;
	if (size > 0)
	{
		l->read_postion += size - 1;
		read_char(l);
	}
	return (tok);
}
