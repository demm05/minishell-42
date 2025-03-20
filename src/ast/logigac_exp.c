/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logigac_exp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelnyk <dmelnyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 11:19:46 by dmelnyk           #+#    #+#             */
/*   Updated: 2025/03/18 11:25:32 by dmelnyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ast_private.h"

t_astnode	*parse_logical_exp(t_token **token)
{
	static t_token_type	exp[] = {AND, OR};
	t_astnode			*left;	
	t_astnode			*head;

	left = parse_pipe(token);
	if (left && match(*token, exp, 2))
	{
		head = new_astnode(*token);
		*token = (*token)->next;
		add_child(head, left);
		add_child(head, parse_logical_exp(token));
		return (head);
	}
	return (left);
}
