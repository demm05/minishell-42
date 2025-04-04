/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelnyk <dmelnyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:40:12 by dmelnyk           #+#    #+#             */
/*   Updated: 2025/03/22 13:24:25 by dmelnyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <signal.h>
#include "minishell.h"

void	prepare_for_the_next_loop(t_data *data)
{
	free(data->line);
	if (data->next_line)
	{
		data->line = data->next_line;
		data->next_line = NULL;
	}
	else
		data->line = NULL;
	if (data->head)
		free_ast(&data->head);
	tmp_del(data->tmp);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	(void)argc;
	data = init(argv, envp);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		if (!data->line)
			interactive_read(data);
		if (!data->line)
			break ;
		split_line(data);
		create_ast(data);
		exec(data);
		prepare_for_the_next_loop(data);
	}
	return (free_everything(data));
}
