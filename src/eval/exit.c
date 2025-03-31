/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelnyk <dmelnyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:40:06 by dmelnyk           #+#    #+#             */
/*   Updated: 2025/03/18 11:02:44 by dmelnyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./eval_private.h"
#include "../heredoc/heredoc.h"
#include <stdlib.h>

bool	handle_exit(t_astnode *head, t_data *data)
{
	int	status;

	status = data->exit_status;
	if (data->head)
		free_ast(&data->head);
	if (data->env)
		free_env(&data->env);
	if (data->tmp)
	{
		tmp_del(data->tmp);
		free(data->tmp->files);
		free(data->tmp->tmpdir);
		free(data->tmp);
	}
	free(data->line);
	exit(status);
}
