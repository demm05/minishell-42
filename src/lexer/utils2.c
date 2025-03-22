/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelnyk <dmelnyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 10:57:40 by dmelnyk           #+#    #+#             */
/*   Updated: 2025/03/22 13:09:16 by dmelnyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./lexer.h"
#include "minishell.h"
#include <stdio.h>

char *decode(t_token_type t)
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
	else if (t == REDIR_OUT)
		return ("REDIR_OUT");
	else if (t == REDIR_IN)
		return ("REDIR_IN");
	else if (t == REDIR_OUT_A)
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
	else if (t == EXPAND_VAR)
		return ("EXPAND_VAR");
	return ("UNKNOWN");
}

void	print_tokens(t_token *token)
{
	printf("Stream of tokens: ");
	while (token->next)
	{
		printf("%s (%s) -> ", decode(token->type), token->literal);
		token = token->next;
	}
	printf("%s (%s)", decode(token->type), token->literal);
	printf("\n\n");
}
