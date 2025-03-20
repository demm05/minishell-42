/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_delete.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelnyk <dmelnyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 10:57:40 by dmelnyk           #+#    #+#             */
/*   Updated: 2025/03/18 10:59:06 by dmelnyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./lexer_private.h"
#include <stdio.h>

char *decode(t_token_type t)
{
	if (t == EOL)
		return ("EOL");
	else if (t == PATH)
		return ("PATH");
	else if (t == ECHO)
		return ("ECHO");
	else if (t == SSPACE)
		return "SPACE";
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
	return ("UNKNOWN");
}

void	print_tokens(t_token *token)
{
	printf("Stream of tokens: ");
	while (token->next)
	{
		printf("%s -> ", decode(token->type));
		token = token->next;
	}
	printf("%s %d", decode(token->type), token->type);
	printf("\n\n");
}
