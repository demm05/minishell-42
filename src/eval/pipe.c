/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelnyk <dmelnyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:40:19 by dmelnyk           #+#    #+#             */
/*   Updated: 2025/03/14 16:43:13 by dmelnyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./eval_private.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

bool	handle_pipe(t_astnode *head, t_data *data)
{
	int	pipefd[2];
	int	pid[2];
	int	status[2];

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return (1);
	}

	pid[0] = fork();
	if (pid[0] == -1)
	{
		perror("fork");
		close(pipefd[0]);
		close(pipefd[1]);
		return (1);
	}
	if (pid[0] == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		if (head->children->type == EXEC)
			exec_command(head->children, data);
		else if (head->children->type == PIPE)
			handle_pipe(head->children, data);
		exit(127);
	}
	pid[1] = fork();
	if (pid[1] == -1)
	{
		perror("fork");
		close(pipefd[0]);
		close(pipefd[1]);
		return (1);
	}
	if (pid[1] == 0)
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		if (head->children->next && head->children->next->type == EXEC)
			exec_command(head->children->next, data);
		else if (head->children->next && head->children->next->type == PIPE)
			handle_pipe(head->children->next, data);
		exit(127);
	}
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid[0], &status[0], 0);
	waitpid(pid[1], &status[1], 0);
	data->exit_status = WEXITSTATUS(status[1]);
	return (0);
}
