/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelnyk <dmelnyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 11:26:53 by dmelnyk           #+#    #+#             */
/*   Updated: 2025/03/22 13:24:59 by dmelnyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ast_private.h"

int	ast_get_size(t_astnode *head)
{
	int	i;

	i = 0;
	while (head)
	{
		i++;
		head = head->next;
	}
	return (i);
}

void	ast_delete_first_child(t_astnode *parent)
{
	t_astnode	*last;
	t_astnode	*next;

	if (!parent || !parent->children)
		return ;
	if (!parent->children->next)
	{
		free(parent->children->literal);
		free(parent->children);
		parent->children = NULL;
		return ;
	}
	last = parent->children->prev;
	next = parent->children->next;
	free(parent->children->literal);
	free(parent->children);
	next->prev = last;
	parent->children = next;
}
