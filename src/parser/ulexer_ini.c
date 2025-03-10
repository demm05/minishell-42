#include "../../inc/parser.h"

t_lexer	*new_lexer(const char *str)
{
	t_lexer	*l;

	if (!str || !*str)
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

t_token	*new_tok(t_lexer *l, t_token_type type, char *s)
{
	t_token	*tok;

	if (!l)
		return (NULL);
	tok = malloc(sizeof(t_token));
	if (!tok)
		return (NULL);
	tok->type = type;
	tok->literal = s; 
	tok->next = NULL;
	tok->prev = NULL;
	return (tok);
}

int	append_token(t_lexer *l, t_token *new)
{
	if (!l)
		return (1);
	if (!new)
		return (0);
	if (!l->tokens)
	{
		new->prev = new;
		l->tokens = new;
	}
	else
	{
		new->prev = l->tokens->prev;
		l->tokens->prev->next = new;
		l->tokens->prev = new;
	}
	return (0);
}

int	append_alloc(t_lexer *l, t_token_type type, int size)
{
	t_token	*new;
	char	*s;
	int		i;
	int		j;

	if (!l)
		return (1);
	s = malloc(sizeof(char) * (size + 1));
	if (!s)
		return (1);
	i = 0;
	j = l->position;
	while (i < size && j < l->size)
		s[i++] = l->input[j++];
	s[i] = 0;
	new = new_tok(l, type, s);
	if (!new)
		free(s);
	l->read_postion += size - 1;
	read_char(l);
	return (append_token(l, new));
}

int	append_advance(t_lexer *l, char *literal, unsigned int advance, t_token_type type)
{
	t_token			*new;
	unsigned int	size;

	if (!l)
	{
		free(literal);
		return (1);
	}
	if (!literal)
		size = 0;
	else
		size = ft_strlen(literal);
	new = new_tok(l, type, literal);
	if (!new)
	{
		free(literal);
		return (1);
	}
	if (advance)
	{
		l->read_postion += advance - 1;
		read_char(l);
	}
	return (append_token(l, new));
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
