/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelnyk <dmelnyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 11:16:37 by dmelnyk           #+#    #+#             */
/*   Updated: 2025/03/18 11:17:34 by dmelnyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ast_private.h"

t_astnode	*parse_pipe(t_token **token)
{
	t_astnode	*left;	
	t_astnode	*head;

	left = parse_redir(token);
	if (left && *token && (*token)->type == PIPE)
	{
		head = new_astnode(*token);
		*token = (*token)->next;
		add_child(head, left);
		add_child(head, parse_pipe(token));
		return (head);
	}
	return (left);
}
