/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelnyk <dmelnyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 12:10:01 by dmelnyk           #+#    #+#             */
/*   Updated: 2025/03/22 14:34:13 by dmelnyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "const_word_private.h"

static inline bool	is_valid_ch(char c)
{
	return (((c >= 'a' && c <= 'z') || \
			(c >= 'A' && c <= 'Z')) || \
			c == '_' || \
			(c >= '0' && c <= '9'));
}

void	lex_env(t_lexer *l)
{
	int			len;
	const char	*str;

	if (peek_char(l) == '?')
	{
		expand_variable(l, NULL, 1, 2);
		return ;
	}
	read_char(l);
	len = 0;
	str = l->input + l->position;
	while (len < l->size && is_valid_ch(str[len]))
		len++;
	expand_variable(l, ft_strndup(l->input + l->position, len), 0, len);
}
