/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelnyk <dmelnyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:26:16 by dmelnyk           #+#    #+#             */
/*   Updated: 2025/03/12 17:43:31 by dmelnyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./lexer_private.h"
#include <stdio.h>

bool	is_token_exec(t_token_type t)
{
	if (t == EXEC || t == CD || t == ECHO || t == PWD)
		return (1);
	if (t == EXPORT || t == UNSET || t == ENV || t == EXIT)
		return (1);
	return (0);
}

char *decode(t_token_type t)
{
	if (t == EXPAND_VAR)
		return ("EXPAND_VAR");
	else if (t == EOL)
		return ("EOL");
	else if (t == SSPACE)
		return ("SPACE");
	else if (t == PATH)
		return ("PATH");
	else if (t == ECHO)
		return ("ECHO");
	else if (t == LT)
		return ("LT");
	else if (t == GT)
		return ("GT");
	else if (t == DLT)
		return ("DLT");
	else if (t == DGT)
		return ("DGT");
	else if (t == DSIGN)
		return ("DSIGN");
	else if (t == RPATH)
		return ("RPATH");
	else if (t == ABSPATH)
		return ("ABSPATH");
	else if (t == ILLEGAL)
		return ("ILLEGAL");
	else if (t == EXIT_STATUS)
		return ("EXIT_STATUS");
	else if (t == SQUOTE)
		return ("SQUOTE");
	else if (t == DQUOTE)
		return ("DQUOTE");
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
	else if (t == VAR_EXP)
		return ("VAR_EXP");
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
