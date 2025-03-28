#include "expansion_private.h"

static inline bool	is_valid_ch(char c)
{
	return (((c >= 'a' && c <= 'z') || \
			(c >= 'A' && c <= 'Z')) || \
			c == '_' || \
			(c >= '0' && c <= '9'));
}

void	lex_env(t_lexer *l)
{
	int			len;
	const char	*str;

	if (peek_char(l) == '?')
	{
		expand_variable(l, NULL, 1, 2);
		return ;
	}
	read_char(l);
	len = 0;
	str = l->input + l->position;
	while (len < l->size && is_valid_ch(str[len]))
		len++;
	expand_variable(l, ft_strndup(l->input + l->position, len), 0, len);
}

bool	is_valid_envv(const char *s)
{
	if (!s || s[0] != '$')
		return (0);
	if (!ft_isalpha(s[1]) && s[1] != '_' && s[1] != '?')
		return (0);
	return (1);
}
