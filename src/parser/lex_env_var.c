#include "../../inc/parser.h"
#include <stdlib.h>

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

t_token *lex_env_var(t_lexer *l)
{
	t_token 	*tok;
	int			len;
	const char	*str;

	// Check if current char is $
	if (l->ch != '$')
		return (NULL);

	if (peek_char(l) == '?')
		return (new_token(EXIT_STATUS, l, 2));

	// Anything that on the begining is not alphabet char and not _ is illegal
	if (!is_valid_ch(peek_char(l)))
		return (new_token(ILLEGAL, l, get_pos_next_whitespace(l)));

	// Eat $
	read_char(l);

	len = 0;
	str = l->input + l->position;
	while (len < l->size && is_valid_ch(str[len]))
		len++;
	tok = new_token(DSIGN, l, len);
	return (tok);
}
