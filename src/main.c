/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelnyk <dmelnyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:40:12 by dmelnyk           #+#    #+#             */
/*   Updated: 2025/04/07 18:20:44 by dmelnyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <signal.h>
#include "minishell.h"

void	prepare_for_the_next_loop(t_data *data)
{
	free(data->line);
	data->line = NULL;
	if (data->head)
		free_ast(&data->head);
	tmp_del(data->tmp);
	update_prompt(data);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	(void)argc;
	data = init(argv, envp);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		interactive_read(data);
		if (!data->line)
			break ;
		create_ast(data);
		exec(data);
		prepare_for_the_next_loop(data);
	}
	return (free_everything(data));
}
