/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyze.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelnyk <dmelnyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 11:24:08 by dmelnyk           #+#    #+#             */
/*   Updated: 2025/03/18 11:27:07 by dmelnyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./lexer_private.h"
#include <stdio.h>

bool	analyze_tokens(t_token *head)
{
	static t_token_type	end[] = {AND, OR, PIPE};
	static t_token_type	redir[] = {REDIR_IN, REDIR_OUT, REDIR_OUT_A, HERE_DOC};
	bool				start;
	bool				status;

	if (!head)
		return (0);
	if (head->prev->type == ILLEGAL)
		return (1);
	// TODO: Here we have to check for here doc
	start = 1;
	status = 0;
	while (head)
	{
		status = 1;
		if (start && match(head, end, 3))
			break ;
		else
			start = 0;
		if (match(head, redir, 4) && !(head->next->type == WORD || \
			(head->next->type == SSPACE && head->next->next && head->next->next->type == WORD)))
		{
			head = head->next;
			break ;
		}
		head = head->next;
		status = 0;
	}
	if (status)
		fprintf(stderr, "syntax error near unexpected token %s\n", decode(head->type));
	return (status);
}
