/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelnyk <dmelnyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:40:16 by dmelnyk           #+#    #+#             */
/*   Updated: 2025/03/12 12:48:29 by dmelnyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./eval_private.h"

bool	handle_unset(t_astnode *head, t_data *data)
{
	if (!head || !data || !head->children)
		return (0);
	head = head->children;
	while (head)
	{
		if (head->literal && ft_strcmp(head->literal, "_") != 0)
			env_unset(&data->env, head->literal);
		head = head->next;
	}
	data->exit_status = 0;
	return (0);
}
