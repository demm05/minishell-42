/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelnyk <dmelnyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 10:38:18 by dmelnyk           #+#    #+#             */
/*   Updated: 2025/03/18 10:50:27 by dmelnyk          ###   ########.fr       */
/*                                                                           */
/* ************************************************************************** */

#include "./lexer_private.h"
#include "../extra/extra.h"
#include <stdio.h>

static bool	condition(char c)
{
	if (ft_isspace(c))
		return (1);
	if (c == '|' || c == '&')
		return (1);
	if (c == '<' || c == '>')
		return (1);
	if (c == '(' || c == ')')
		return (1);
	return (0);
}

void	add_word(t_lexer *l)
{
	const char	*s;
	int			i;
	bool		dquote;
	bool		squote;

	dquote = 0;
	squote = 0;
	s = l->input + l->position;
	i = -1;
	while (s[++i])
	{
		if (s[i] == '"' && !squote)
			dquote = !dquote;
		else if (s[i] == '\'' && !dquote)
			squote = !squote;
		else if (!dquote && !squote && condition(s[i]))
			break ;
	}
	if (squote || dquote)
		append_advance(l, NULL, 0, ILLEGAL);
	else
		append_alloc(l, WORD, i);
}
