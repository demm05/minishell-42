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

int	free_data(t_data *data)
{
	free(data->line);
	data->line = NULL;
	return (0);
}

t_data	*init(int argc, char **argv, char **envp)
{
	t_data	*data;

	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		return (NULL);
	data->env = init_env(argv, envp);
	data->prompt = "Prompt > ";
	return (data);
}
