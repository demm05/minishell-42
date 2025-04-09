/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_quote.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelnyk <dmelnyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 18:24:12 by dmelnyk           #+#    #+#             */
/*   Updated: 2025/04/07 18:24:12 by dmelnyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion_private.h"

static void	read_squote(t_lexer *l)
{
	int	pos;

	pos = l->position;
	while (pos < l->size && l->input[pos] != '\'')
		pos++;
	append_alloc(l, WORD, pos - l->position);
}

static int	process_character(t_lexer *l, const char **s, int *i, bool *escape)
{
	if (*escape)
	{
		*escape = 0;
		append_advance(l, ft_strndup(*s, *i - 1), *i, WORD);
		*s = l->input + l->position;
		*i = 0;
	}
	else if ((*s)[*i] == '\\')
		*escape = !(*escape);
	else if ((*s)[*i] == '"')
		return (1);
	else if ((*s)[*i] == '$' && is_valid_envv(*s + *i))
	{
		if (*i > 0)
			append_alloc(l, WORD, *i);
		lex_env(l, 0);
		*s = l->input + l->position;
		*i = 0;
		return (0);
	}
	*i += 1;
	return (0);
}

static void	read_dquote(t_lexer *l)
{
	const char	*s;
	int			i;
	bool		escape;

	i = 0;
	escape = 0;
	s = l->input + l->position;
	while (s[i])
	{
		if (process_character(l, &s, &i, &escape))
			break ;
	}
	if (i > 0)
		append_alloc(l, WORD, i);
}

void	lex_quote(t_lexer *l)
{
	char	c;

	c = l->ch;
	if (c != '\'' && c != '"')
		return ;
	append_advance(l, NULL, 1, QUOTE);
	if (c == '\'')
		read_squote(l);
	else if (c == '"')
		read_dquote(l);
	append_advance(l, NULL, 1, QUOTE);
}
