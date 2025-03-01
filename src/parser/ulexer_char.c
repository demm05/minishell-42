#include "../../inc/parser.h"

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

void	eat_whitespaces(t_lexer *l)
{
	while (l->ch == ' ' || l->ch == '\t' || l->ch == '\r' || l->ch == '\n')
		read_char(l);
}

int	get_pos_next_whitespace(t_lexer *l)
{
	int		i;

	i = l->read_postion;
	while (i < l->size)
	{
		if (ft_isspace(l->input[i]))
			break ;
		if (!l->input[i])
			break ;
		i++;
	}
	return (i - l->read_postion + 1);
}
