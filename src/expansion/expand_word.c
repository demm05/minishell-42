/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelnyk <dmelnyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 18:23:43 by dmelnyk           #+#    #+#             */
/*   Updated: 2025/04/07 18:23:44 by dmelnyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion_private.h"
#include <stdio.h>

t_token	**get_array(t_token *token, bool split_it);

char	**expand_word(t_astnode *head, t_data *data, bool split_it)
{
	t_token	*token;
	t_token	**arr;
	char	**res;

	if (!head || !head->literal)
		return (NULL);
	token = word_generate_tokens(head->literal, data);
	if (!token)
		return (NULL);
	if (DEBUG)
		print_tokens(token);
	arr = get_array(token, split_it);
	if (!arr)
	{
		perror("malloc\n");
		return (NULL);
	}
	res = join_tokens(arr);
	free(arr);
	return (res);
}

t_token	**get_array(t_token *token, bool split_it)
{
	t_token	**arr;

	if (split_it)
		return (split_tokens(token));
	arr = malloc(sizeof(t_token *) * 2);
	if (!arr)
		return (NULL);
	arr[0] = token;
	arr[1] = NULL;
	return (arr);
}
