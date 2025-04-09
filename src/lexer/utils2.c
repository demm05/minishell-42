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

#include "minishell.h"

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

bool	is_redir(t_token_type t)
{
	return (t == REDIR_OUT || t == REDIR_OUT_A || \
		t == REDIR_IN || t == HERE_DOC);
}
