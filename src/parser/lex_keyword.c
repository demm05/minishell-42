#include "../../inc/parser.h"
#include "libft.h"

int	lex_keyword(t_lexer *l)
{
	static const t_keyword	keys[] = {
	{"echo", ECHO, 4}, {"pwd", PWD, 3}, {"cd", CD, 2}, {"export", EXPORT, 6},
	{"env", ENV, 3}, {"unset", UNSET, 5}, {"exit", EXIT, 4}, {"clear", CLEAR, 5}
	};
	int		i;
	int		size;
	char	c;

	if (!ft_isalpha(l->ch) || !ft_isalpha(peek_char(l)))
		return (0);

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
		return (!append_token(l, keys[i].type, keys[i].size));
	}
	return (0);
}
