/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelnyk <dmelnyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 16:31:26 by dmelnyk           #+#    #+#             */
/*   Updated: 2025/03/22 19:08:40 by dmelnyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "const_word_private.h"
#include <stdio.h>

static unsigned int	get_list_size(t_token *head)
{
	unsigned int	len;

	len = 0;
	while (head)
	{
		len += head->size;
		head = head->next;
	}
	return (len);
}

static char	*join_head(t_token *head)
{
	char			*res;
	unsigned int	size;
	int				j;
	int				k;

	j = 0;
	size = get_list_size(head);
	res = malloc(sizeof(char) *(size + 1));
	if (!res)
	{
		perror("malloc");
		return (NULL);
	}
	while (head)
	{
		k = 0;
		while (k < head->size)
			res[j++] = head->literal[k++];
		head = head->next;;
	}
	res[j] = 0;
	return (res);
}

static int	get_arr_size(t_token **head)
{
	int		size;

	if (!head || !*head)
		return (0);
	size = 0;
	while (head[size])
		size++;
	return (size);
}

char	**join_tokens(t_token **head)
{
	char	**res;
	char	*s;
	t_token	*cur;
	t_token	*next;
	int		i;

	if (!head || !*head)
		return (NULL);
	res = malloc(sizeof(char *) * (get_arr_size(head) + 1));
	if (!res)
	{
		perror("malloc");
		return (NULL);
	}
	i = 0;
	cur = *head;
	while (cur)
	{
		next = cur->next;
		s = join_head(cur);
		free_tokens(&cur);
		res[i++] = s;
		cur = next;
	}
	res[i] = NULL;
	return (res);
}
