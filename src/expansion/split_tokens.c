/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelnyk <dmelnyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 18:24:14 by dmelnyk           #+#    #+#             */
/*   Updated: 2025/04/07 18:24:14 by dmelnyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion_private.h"

static inline int	get_size(t_token *head)
{
	int		size;
	bool	state;

	size = 0;
	state = 0;
	while (head)
	{
		if (head->type == SSPACE)
			state = 0;
		else if (!state)
		{
			state = 1;
			size++;
		}
		head = head->next;
	}
	return (size);
}

t_token	**split_tokens(t_token *head)
{
	t_token	**res;
	t_token	*next;
	int		i;

	res = malloc(sizeof(char *) * (get_size(head) + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (head)
	{
		res[i] = head;
		while (head->next && head->type != SSPACE)
			head = head->next;
		next = head->next;
		if (next)
			next->prev = res[i]->prev;
		head->next = NULL;
		res[i++]->prev = head;
		head = next;
	}
	res[i] = NULL;
	return (res);
}
