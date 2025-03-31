#include "expansion_private.h"
#include <stdlib.h>

bool	is_valid_envv(const char *s)
{
	if (!s || s[0] != '$')
		return (0);
	if (!ft_isalpha(s[1]) && s[1] != '_' && s[1] != '?')
		return (0);
	return (1);
}

static inline bool	is_valid_ch(char c)
{
	return (((c >= 'a' && c <= 'z') || \
			(c >= 'A' && c <= 'Z')) || \
			c == '_' || \
			(c >= '0' && c <= '9'));
}

char	*getenv_key(const char *s)
{
	const char	*anch;

	if (!is_valid_envv(s))
		return (NULL);
	s++;
	if (*s == '?')
		return (ft_strdup("?"));
	anch = s;
	while (*s && is_valid_ch(*s))
		s++;
	return (ft_strndup(anch, s - anch));
}

void	lex_env(t_lexer *l)
{
	char		*key;

	if (!is_valid_envv(l->input + l->position))
		return ;
	if (peek_char(l) == '?')
	{
		expand_variable(l, NULL, 1, 2);
		return ;
	}
	key = getenv_key(l->input + l->position);
	expand_variable(l, key, 0, ft_strlen(key) + 1);
}
