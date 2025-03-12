/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_keyword.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelnyk <dmelnyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:26:04 by dmelnyk           #+#    #+#             */
/*   Updated: 2025/03/12 12:26:06 by dmelnyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./lexer_private.h"
#include "../extra/extra.h"
#include "libft.h"
#include <stdlib.h>

int	lex_keyword(t_lexer *l)
{
	static t_keyword	keys[] = {
	{"echo", ECHO, 4}, {"pwd", PWD, 3}, {"cd", CD, 2}, {"export", EXPORT, 6},
	{"env", ENV, 3}, {"unset", UNSET, 5}, {"exit", EXIT, 4}
	};
	int					i;
	int					size;
	char				c;

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
		return (!append_advance(l, NULL, keys[i].size, keys[i].type));
	}
	return (0);
}
