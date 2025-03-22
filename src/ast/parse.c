/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelnyk <dmelnyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 11:20:41 by dmelnyk           #+#    #+#             */
/*   Updated: 2025/03/22 19:26:08 by dmelnyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast_private.h"

void	create_ast(t_data *data)
{
	t_token	*head;
	t_token	*ptr;

	if (!data->line)
		return ;
	head = generate_tokens(data->line);
	//print_tokens(head);
	if (analyze_tokens(head))
	{
		free_tokens(&head);
		data->exit_status = 2;
		return ;
	}
	ptr = head;
	data->head = parse_logical_exp(&ptr);
	//print_ast(data->head, 0);
	free_tokens(&head);
}
