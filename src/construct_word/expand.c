/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelnyk <dmelnyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 12:04:07 by dmelnyk           #+#    #+#             */
/*   Updated: 2025/03/22 19:08:05 by dmelnyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "const_word_private.h"
#include <stdio.h>

static inline char	**expand_word(t_astnode *head, t_data *data)
{
	t_token	*token;
	t_token	**arr;
	char	**res;

	if (!head || !head->literal)
		return (NULL);
	token = word_generate_tokens(head->literal);
	if (!token)
		return (NULL);
	arr = NULL;
	//arr = process_tokens(token, data);
	//expand_variables(token, data);
	//print_tokens(token);
	//arr = wildcard_it(&token);
	//free_tokens(&token);
	res = join_tokens(arr);
	free(arr);
	return (res);
}

static inline bool	statement(t_token_type t)
{
	return (t == WORD || t == PATH || t == EXEC);
}

static inline void	do_stuff_with_head(t_astnode *head, t_data *data)
{
	char	**s;

	if (!head || !head->literal)
		return ;
	if (!statement(head->type))
		return ;
	s = expand_word(head, data);
	if (!s)
		return ;
	free(head->literal);
	head->literal = *s;
	free(s);
}

void	expand_head(t_astnode *head, t_data *data)
{
	t_astnode	*cur;

	if (!head || !data || !statement(head->type))
		return ;
	do_stuff_with_head(head, data);
	cur = head->children;
	while (cur)
	{
		do_stuff_with_head(cur, data);
		cur = cur->next;
	}
}
