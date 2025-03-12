/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_generic.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelnyk <dmelnyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:26:02 by dmelnyk           #+#    #+#             */
/*   Updated: 2025/03/12 12:26:02 by dmelnyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./lexer_private.h"

int	is_there_exec(t_lexer *l)
{
	t_token				*last;

	if (!l->tokens)
		return (0);
	last = l->tokens->prev;
	while (1)
	{
		if (is_token_exec(last->type))
			return (1);
		if (last->type == AND || last->type == OR || last->type == PIPE)
			break ;
		last = last->prev;
		if (!last->next)
			break ;
	}
	return (0);
}

int	lex_executable(t_lexer *l)
{
	append_alloc(l, EXEC, get_pos_next_whitespace(l));
	return (1);
}

int	lex_word(t_lexer *l)
{
	append_alloc(l, WORD, get_pos_next_whitespace(l));
	return (1);
}
