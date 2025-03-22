/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_quote.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelnyk <dmelnyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 11:50:02 by dmelnyk           #+#    #+#             */
/*   Updated: 2025/03/22 13:21:06 by dmelnyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "const_word_private.h"

static void	read_squote(t_lexer *l)
{
	int	pos;

	pos = l->position;
	while (pos < l->size && l->input[pos] != '\'')
		pos++;
	append_alloc(l, WORD, pos - l->position);
	read_char(l);
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
		if (escape)
			escape = 0;
		else if (s[i] == '\\')
			escape = !escape;
		else if (s[i] == '"')
			break ;
		else if (is_valid_envv(s + i))
		{
			if (i > 0)
				append_alloc(l, WORD, i);
			lex_env(l);
			i = 0;
			s = l->input + l->position;
			continue ;
		}
		i++;
	}
	if (i > 0)
		append_alloc(l, WORD, i);
	read_char(l);
}

void	lex_quote(t_lexer *l)
{
	if (l->ch == '\'')
	{
		read_char(l);
		read_squote(l);
	}
	else if (l->ch == '"')
	{
		read_char(l);
		read_dquote(l);
	}
}
