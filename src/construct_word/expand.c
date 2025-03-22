/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelnyk <dmelnyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 12:04:07 by dmelnyk           #+#    #+#             */
/*   Updated: 2025/03/22 14:58:41 by dmelnyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "const_word_private.h"
#include <stdio.h>

void	expand_variables(t_token *tok, t_data *data);

char	**expand_word(t_astnode *head, t_data *data)
{
	t_token	*token;

	if (!head || !head->literal)
		return (NULL);
	token = word_generate_tokens(head->literal);
	if (!token)
		return (NULL);
	expand_variables(token, data);
	//wildcard_it();
	print_tokens(token);
	free_tokens(&token);
	return (NULL);
}

static bool	statement(t_token_type t)
{
	return (t == WORD || t == PATH || t == EXEC);
}

void	expand_head(t_astnode *head, t_data *data)
{
	t_astnode	*cur;

	if (!head || !data)
		return ;
	if (!statement(head->type))
		return ;
	expand_word(head, data);
	cur = head->children;
	while (cur)
	{
		if (statement(cur->type))
			expand_word(cur, data);
		cur = cur->next;
	}
}
