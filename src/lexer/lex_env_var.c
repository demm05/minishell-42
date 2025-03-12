#include "./lexer_private.h"
#include <stdbool.h>

static inline bool	is_valid_ch(char c)
{
	return (((c >= 'a' && c <= 'z') || \
			(c >= 'A' && c <= 'Z')) || \
			c == '_' || \
			(c >= '0' && c <= '9'));
}

int	lex_env_var(t_lexer *l)
{
	int			len;
	const char	*str;

	if (l->ch != '$')
		return (0);
	if (peek_char(l) == '?')
		return (!append_alloc(l, EXIT_STATUS, 2));
	if (!is_valid_ch(peek_char(l)))
		return (!append_alloc(l, ILLEGAL, get_pos_next_whitespace(l)));
	read_char(l);
	len = 0;
	str = l->input + l->position;
	while (len < l->size && is_valid_ch(str[len]))
		len++;
	append_alloc(l, EXPAND_VAR, len);
	return (1);
}
