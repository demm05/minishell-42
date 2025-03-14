/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelnyk <dmelnyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:26:22 by dmelnyk           #+#    #+#             */
/*   Updated: 2025/03/14 15:21:06 by dmelnyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./lexer_private.h"
#include "../extra/extra.h"
#include <stdlib.h>

void	read_char(t_lexer *l)
{
	if (l->read_postion >= l->size)
		l->ch = 0;
	else
		l->ch = l->input[l->read_postion];
	l->position = l->read_postion;
	l->read_postion += 1;
}

char	peek_char(t_lexer *l)
{
	if (l->read_postion >= l->size)
		return (0);
	return (l->input[l->read_postion]);
}

void	eat_whitespaces(t_lexer *l)
{
	//if (l->tokens && l->tokens->prev->type != SSPACE && ft_isspace(l->ch))
	//	append_token(l, new_token(SSPACE, NULL));
	while (l->ch == ' ' || l->ch == '\t' || l->ch == '\r' || l->ch == '\n')
		read_char(l);
}

int	get_pos_next_whitespace(t_lexer *l)
{
	int		i;

	i = l->read_postion;
	while (i < l->size)
	{
		if (ft_isspace(l->input[i]))
			break ;
		if (!l->input[i])
			break ;
		i++;
	}
	return (i - l->read_postion + 1);
}
