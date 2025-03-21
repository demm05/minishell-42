/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelnyk <dmelnyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 10:53:57 by dmelnyk           #+#    #+#             */
/*   Updated: 2025/03/21 14:19:23 by dmelnyk          ###   ########.fr       */
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
	while (ft_isspace(l->ch))
		read_char(l);
}

bool	is_token_exec(t_token_type t)
{
	if (t == EXEC || t == CD || t == ECHO || t == PWD)
		return (1);
	if (t == EXPORT || t == UNSET || t == ENV || t == EXIT)
		return (1);
	return (0);
}

bool	match(t_token *token, t_token_type expected[], int size)
{
	if (!token)
		return (0);
	while (size-- > 0)
	{
		if (*expected == token->type)
			return (1);
		expected++;
	}
	return (0);
}

bool	is_redir(t_token_type t)
{
	return (t == REDIR_OUT || t == REDIR_OUT_A || t == REDIR_IN || t == HERE_DOC);
}

