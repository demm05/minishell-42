/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelnyk <dmelnyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:52:53 by dmelnyk           #+#    #+#             */
/*   Updated: 2025/03/22 11:28:06 by dmelnyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "extra_private.h"
#include <readline/readline.h>

t_data	*init(char **argv, char **envp)
{
	t_data	*data;

	data = ft_calloc(1, sizeof(t_data));
	if (!data)
	{
		perror("malloc");
		return (NULL);
	}
	data->env = env_init(argv, envp);
	data->tmp = tmp_alloc();
	data->prompt = "Prompt > ";
	return (data);
}

int	free_everything(t_data *data)
{
	int		status;

	status = data->exit_status;
	if (data->head)
		free_ast(&data->head);
	if (data->env)
		env_free(&data->env);
	if (data->tmp)
	{
		tmp_del(data->tmp);
		free(data->tmp->files);
		free(data->tmp->tmpdir);
		free(data->tmp);
	}
	rl_clear_history();
	free(data->line);
	free(data);
	return (status);
}
