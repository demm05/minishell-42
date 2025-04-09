/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelnyk <dmelnyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 11:20:41 by dmelnyk           #+#    #+#             */
/*   Updated: 2025/04/07 18:23:06 by dmelnyk          ###   ########.fr       */
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
	if (analyze_tokens(data, head))
	{
		free_tokens(&head, 1);
		data->exit_status = 2;
		return ;
	}
	ptr = head;
	data->head = parse_sequence(&ptr);
	if (ptr && ptr->type != EOL)
	{
		fprintf(stderr, "failed to create complete ast\n");
		free_tokens(&ptr->next, 1);
	}
	free_tokens(&head, 0);
}
