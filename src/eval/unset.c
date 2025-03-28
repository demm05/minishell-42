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
		env_unset(&data->env, head->literal);
		head = head->next;
	}
	return (0);
}
