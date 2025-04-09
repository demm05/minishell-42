/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decode.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelnyk <dmelnyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:57:34 by dmelnyk           #+#    #+#             */
/*   Updated: 2025/04/09 15:57:34 by dmelnyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline char	*_decode1(t_token_type t)
{
	if (t == EOL)
		return ("EOL");
	else if (t == EXIT_STATUS)
		return ("EXIT_STATUS");
	else if (t == PATH)
		return ("PATH");
	else if (t == LPAREN)
		return ("LPAREN");
	else if (t == RPAREN)
		return ("RPAREN");
	else if (t == ECHO)
		return ("ECHO");
	else if (t == ILLEGAL)
		return ("ILLEGAL");
	else if (t == AND)
		return ("AND");
	else if (t == OR)
		return ("OR");
	else if (t == SEQUENCE)
		return ("SEQUENCE");
	else if (t == REDIR_OUT)
		return ("REDIR_OUT");
	else if (t == REDIR_IN)
		return ("REDIR_IN");
	return (NULL);
}

static inline char	*_decode2(t_token_type t)
{
	if (t == REDIR_OUT_A)
		return ("REDIR_OUT_A");
	else if (t == HERE_DOC)
		return ("HERE_DOC");
	else if (t == PIPE)
		return ("PIPE");
	else if (t == EXEC)
		return ("EXEC");
	else if (t == WORD)
		return ("WORD");
	else if (t == CD)
		return ("CD");
	else if (t == PWD)
		return ("PWD");
	else if (t == EXPORT)
		return ("EXPORT");
	else if (t == UNSET)
		return ("UNSET");
	else if (t == ENV)
		return ("ENV");
	else if (t == EXIT)
		return ("EXIT");
	else if (t == WILDCARD)
		return ("WILDCARD");
	return (NULL);
}

static inline char	*_decode3(t_token_type t)
{
	if (t == EXPAND_VAR)
		return ("EXPAND_VAR");
	else if (t == QUOTE)
		return ("QUOTE");
	return (NULL);
}

char	*decode(t_token_type t)
{
	char	*s;

	s = _decode1(t);
	if (s)
		return (s);
	s = _decode2(t);
	if (s)
		return (s);
	s = _decode3(t);
	if (s)
		return (s);
	return ("UNKNOWN");
}
