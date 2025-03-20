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
#include <stdlib.h>

t_astnode	*parse_exec(t_token *token)
{
	static t_token_type	end[] = {AND, OR, PIPE};
	static t_token_type	fine[] = {WORD, PATH};
	static t_token_type	redir[] = {REDIR_IN, REDIR_OUT, REDIR_OUT_A, HERE_DOC};
	t_astnode	*head;

	head = NULL;
	while (token)
	{
		while (match(token, redir, 4))
		{
			token = token->next;
			if (token)
				token = token->next;
		}
		if (!head)
		{
			head = new_astnode(token);
			head->type = EXEC;
			token = token->next;
			continue ;
		}
		if (!token || match(token, end, 3))
			break ;
		else if (match(token, fine, 2))
			add_child(head, new_astnode(token));
		token = token->next;
	}
	return (head);
}
