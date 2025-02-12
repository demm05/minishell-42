#include "../../inc/parser.h"
#include "../../inc/minishell.h"
#include "libft.h"
#include <stdlib.h>

int	get_pos_next_whitespace(t_lexer *l)
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
	return (i);
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
	if (!ft_isalpha(peek_char(l)) && peek_char(l) != '_' && !ft_isdigit(peek_char(l)))
		return (new_token(ILLEGAL, l, get_pos_next_whitespace(l)));

	// Eat $
	read_char(l);

	len = 0;
	str = l->input + l->position;

	while (len < l->size && (ft_isalpha(str[len]) || str[len] == '_' || ft_isdigit(str[len])))
		len++;
	if (len < l->size  && !(ft_isspace(str[len]) || str[len] == '$'))
		tok = new_token(ILLEGAL, l, get_pos_next_whitespace(l));
	else
		tok = new_token(DSIGN, l, len);
	return (tok);
}
