/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelnyk <dmelnyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 16:35:53 by dmelnyk           #+#    #+#             */
/*   Updated: 2025/04/09 16:35:54 by dmelnyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion_private.h"

bool	is_there_wildcard(t_token *head)
{
	while (head)
	{
		if (head->type == WILDCARD)
			return (true);
		head = head->next;
	}
	return (false);
}

static int	get_size(t_token **arr, char **targets)
{
	int	i;
	int	j;
	int	size;

	i = 0;
	size = 0;
	while (arr[i])
	{
		if (is_there_wildcard(arr[i]))
		{
			j = 0;
			while (targets[j])
				if (match_pattern(arr[i], targets[j++]))
					size++;
		}
		size++;
		i++;
	}
	return (size);
}

void	init_wildcards(t_token **arr, char ***targets, t_token ***res)
{
	*targets = dir_get_content_list(".");
	*res = malloc(sizeof(t_token *) * (get_size(arr, *targets) + 1));
	if (!*res)
		dir_free_list(*targets);
}
