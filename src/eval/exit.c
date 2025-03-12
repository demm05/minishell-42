/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelnyk <dmelnyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:40:06 by dmelnyk           #+#    #+#             */
/*   Updated: 2025/03/12 12:47:15 by dmelnyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./eval_private.h"
#include "../lexer/lexer.h"
#include <stdlib.h>
#include <stdio.h>

bool	handle_exit(t_astnode *head, t_data *data)
{
	int	status;

	status = data->exit_status;
	if (data->l)
		free_lexer(data->l);
	if (data->head)
		free_ast(&data->head);
	if (data->env)
		free_env(&data->env);
	free(data->line);
	fprintf(stderr, "exit\n");
	exit(status);
}
