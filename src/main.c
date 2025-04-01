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
#include <stdlib.h>
#include <readline/readline.h>
#include <unistd.h>
#include "extra/extra.h"
#include "ast/ast.h"
#include "heredoc/heredoc.h"
#include "signal.h"

void	prepare_for_the_next_loop(t_data *data)
{
	free(data->line);
	data->line = NULL;
	if (data->head)
		free_ast(&data->head);
	tmp_del(data->tmp);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;
	int		status;

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
	free_env(&data->env);
	free(data->tmp->files);
	free(data->tmp->tmpdir);
	free(data->tmp);
	status = data->exit_status;
	rl_clear_history();
	free(data);
	return (status);
}
