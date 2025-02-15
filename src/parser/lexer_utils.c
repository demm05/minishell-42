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
	l->position = l->read_postion;
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

bool	ft_isspace(char ch)
{
	return ((ch == ' ' || ch == '\t' || ch == 'r' || ch == 'n'));
}

void	eat_whitespaces(t_lexer *l)
{
	while (l->ch == ' ' || l->ch == '\t' || l->ch == '\r' || l->ch == '\n')
		read_char(l);
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
