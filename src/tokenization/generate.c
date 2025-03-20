/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelnyk <dmelnyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 10:37:10 by dmelnyk           #+#    #+#             */
/*   Updated: 2025/03/18 11:06:56 by dmelnyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./lexer_private.h"
#include "libft.h"
#include <stdlib.h>

bool	is_fixed_type(t_lexer *l);
void	add_word(t_lexer *l);

void	generate_tokens(t_data *data)
{
	t_lexer *l;

	l = data->l;
	l->input = data->line;
	l->size = ft_strlen(data->line);
	read_char(l);
	while (l->position < l->size)
	{
		if (l->tokens && l->tokens->prev->type == ILLEGAL)
			return ;
		eat_whitespaces(l);
		if (is_fixed_type(l))
			continue ;
		else if (l->ch)
			add_word(l);
		else
			break ;
	}
	append_advance(l, NULL, 0, EOL);
}

bool	is_fixed_type(t_lexer *l)
{
	if (l->ch == '|' && peek_char(l) == '|')
		append_advance(l, NULL, 2, OR);
	else if (l->ch == '|')
		append_advance(l, NULL, 1, PIPE);
	else if (l->ch == '&' && peek_char(l) == '&')
		append_advance(l, NULL, 2, AND);
	else if (l->ch == '&')
		append_advance(l, NULL, 2, ILLEGAL);
	else if (l->ch == '>' && peek_char(l) == '>')
		append_advance(l, NULL, 2, REDIR_OUT_A);
	else if (l->ch == '>')
		append_advance(l, NULL, 1, REDIR_OUT);
	else if (l->ch == '<' && peek_char(l) == '<')
		append_advance(l, NULL, 2, HERE_DOC);
	else if (l->ch == '<')
		append_advance(l, NULL, 1, REDIR_IN);
	else
		return (0);
	return (1);
}
