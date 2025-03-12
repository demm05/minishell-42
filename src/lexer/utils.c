/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelnyk <dmelnyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:26:16 by dmelnyk           #+#    #+#             */
/*   Updated: 2025/03/12 16:20:52 by dmelnyk          ###   ########.fr       */
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
	if (EXPAND_VAR)
		return ("EXPAND_VAR");
	else if (EOL)
		return ("EOL");
	else if (SSPACE)
		return ("SPACE");
	else if (PATH)
		return ("PATH");
	else if (ECHO)
		return ("ECHO");
	else if (LT)
		return ("LT");
	else if (GT)
		return ("GT");
	else if (DLT)
		return ("DLT");
	else if (DGT)
		return ("DGT");
	else if (DSIGN)
		return ("DSIGN");
	else if (RPATH)
		return ("RPATH");
	else if (ABSPATH)
		return ("ABSPATH");
	else if (ILLEGAL)
		return ("ILLEGAL");
	else if (EXIT_STATUS)
		return ("EXIT_STATUS");
	else if (SQUOTE)
		return ("SQUOTE");
	else if (DQUOTE)
		return ("DQUOTE");
	else if (AND)
		return ("AND");
	else if (OR)
		return ("OR");
	else if (REDIR_OUT)
		return ("REDIR_OUT");
	else if (REDIR_IN)
		return ("REDIR_IN");
	else if (REDIR_OUT_A)
		return ("REDIR_OUT_A");
	else if (HERE_DOC)
		return ("HERE_DOC");
	else if (PIPE)
		return ("PIPE");
	else if (VAR_EXP)
		return ("VAR_EXP");
	else if (EXEC)
		return ("EXEC");
	else if (WORD)
		return ("WORD");
	else if (CD)
		return ("CD");
	else if (PWD)
		return ("PWD");
	else if (EXPORT)
		return ("EXPORT");
	else if (UNSET)
		return ("UNSET");
	else if (ENV)
		return ("ENV");
	else if (EXIT)
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
