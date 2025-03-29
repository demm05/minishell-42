/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelnyk <dmelnyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:40:22 by dmelnyk           #+#    #+#             */
/*   Updated: 2025/03/22 18:44:39 by dmelnyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./eval_private.h"
#include "minishell.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

bool	handle_exec(t_astnode *head, t_data *data)
{
	int		pid;
	int		status;

	if (!*head->literal)
		return (0);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
	{
		reset_signals();
		exec_command(head, data);
		exit(127);
	}
	else
		waitpid(pid, &status, 0);
	data->exit_status = status >> 8;
	if (status)
		return (1);
	return (0);
}
