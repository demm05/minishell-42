/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelnyk <dmelnyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 11:08:49 by dmelnyk           #+#    #+#             */
/*   Updated: 2025/03/18 11:16:15 by dmelnyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ast_private.h"

t_astnode	*parse_exec(t_token *token)
{
	static t_token_type	end[] = {AND, OR, PIPE, SEQUENCE};
	static t_token_type	redir[] = {REDIR_IN, REDIR_OUT, REDIR_OUT_A, HERE_DOC};
	t_astnode			*head;

	head = NULL;
	while (token)
	{
		while (token && match(token, redir, 4))
		{
			token = token->next;
			token = token->next;
		}
		if (!head && token && token->type == WORD)
		{
			head = new_astnode(token);
			head->type = EXEC;
		}
		else if (!token || match(token, end, 4))
			break ;
		else if (token && (token->type == WORD))
			add_child(head, new_astnode(token));
		token = token->next;
	}
	return (head);
}
