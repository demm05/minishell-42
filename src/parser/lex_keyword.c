#include "../../inc/parser.h"
#include "../../inc/minishell.h"
#include "libft.h"
#include <stdlib.h>

t_token	*lex_keyword(t_lexer *l)
{
	static const t_keyword	keys[] = {
	{"echo", ECHO, 4}, {"pwd", PWD, 3}, {"cd", CD, 2}, {"export", EXPORT, 6},
	{"env", ENV, 3}, {"unset", UNSET, 5}, {"exit", EXIT, 4}, {"clear", CLEAR, 5}
	};
	int		i;
	int		size;
	char	c;

	if (!ft_isalpha(l->ch) || !ft_isalpha(peek_char(l)))
		return (NULL);

	i = -1;
	size = sizeof(keys) / sizeof(keys[0]);
	while (++i < size)
	{
		if (l->position + keys[i].size > l->size)
			continue ;
		if (ft_strncmp(l->input + l->position, keys[i].key, keys[i].size) != 0)
			continue ;
		c = l->input[l->position + keys[i].size];
		if (c && !ft_isspace(c))
			break ;
		return (new_token(keys[i].type, l, keys[i].size));
	}
	return (NULL);
}
