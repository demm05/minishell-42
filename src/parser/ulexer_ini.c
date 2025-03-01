#include "../../inc/parser.h"

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

void	free_lexer(t_lexer *l)
{
	t_token	*next;

	if (!l)
		return ;
	while (l->tokens)
	{
		next = l->tokens->next;
		free(l->tokens);
		l->tokens = next;
	}
	free(l);
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
		new->prev = l->tokens->prev;
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
