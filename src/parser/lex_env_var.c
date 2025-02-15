#include "../../inc/parser.h"

static inline int	get_pos_next_whitespace(t_lexer *l)
{
	int		i;

	i = -1;
	while (1)
	{
		i++;
		if (l->position + i > l->size)
			break ;
		if (ft_isspace(l->input[l->position + i]))
			break ;
		while (l->position + i > l->size && l->input[l->position + i] == '$')
			i++;
	}
	if (i > l->size)
		i = l->size;
	return (i);
}

static inline bool	is_valid_ch(char c)
{
	return (((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) || c == '_' || (c >= '0' && c <= '9'));
}

int	lex_env_var(t_lexer *l)
{
	int			len;
	const char	*str;

	// Check if current char is $
	if (l->ch != '$')
		return (0);

	if (peek_char(l) == '?')
		return (!append_token(l, EXIT_STATUS, 2));

	// The next char after $ could be only alpha char, digit or _
	if (!is_valid_ch(peek_char(l)))
		return (!append_token(l, ILLEGAL, get_pos_next_whitespace(l)));

	// Eat $
	read_char(l);

	len = 0;
	str = l->input + l->position;
	while (len < l->size && is_valid_ch(str[len]))
		len++;
	append_token(l, DSIGN, len);
	return (1);
}
