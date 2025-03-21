/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelnyk <dmelnyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 11:20:41 by dmelnyk           #+#    #+#             */
/*   Updated: 2025/03/21 16:16:26 by dmelnyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ast_private.h"
#include "libft.h"
#include <stdio.h>

void	create_ast(t_data *data)
{
	t_token	*head;

	if (!data->line)
		return ;
	generate_tokens(data);
	print_tokens(data->l->tokens);
	if (analyze_tokens(data->l->tokens))
	{
		free_tokens(&data->l->tokens);
		data->exit_status = 2;
		return ;
	}
	head = data->l->tokens;
	data->head = parse_logical_exp(&head);
	if (!data->head)
	{
		puts("There is no ast head");
		return ;
	}
	print_ast(data->head, 0);
}
