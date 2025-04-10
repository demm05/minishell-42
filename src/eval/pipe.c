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

#include "eval_private.h"
#include <sys/types.h>
#include <sys/wait.h>

int	fork_it(t_astnode *head, t_data *data, bool id, int pipefd[2])
{
	int	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("pipe");
		close(pipefd[0]);
		close(pipefd[1]);
		return (-1);
	}
	if (pid != 0)
		return (pid);
	close(pipefd[id]);
	dup2(pipefd[!id], !id);
	close(pipefd[!id]);
	if (head->type == EXEC)
		exec_command(head, data);
	else
		eval(head, data);
	exit(free_everything(data));
}

int	get_final_status(int status[2])
{
	status[0] = get_childs_status(status[0]);
	status[1] = get_childs_status(status[1]);
	if (status[0] == 131 || status[1] == 131)
		return (131);
	else if (status[0] == 130 || status[1] == 130)
		return (130);
	return (status[1]);
}

bool	handle_pipe(t_astnode *head, t_data *data)
{
	int	pipefd[2];
	int	pid[2];
	int	status[2];

	if (!head || !head->children || !head->children->next)
		return (1);
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return (1);
	}
	pid[0] = fork_it(head->children, data, 0, pipefd);
	if (pid[0] == -1)
		return (1);
	pid[1] = fork_it(head->children->next, data, 1, pipefd);
	if (pid[1] == -1)
		return (1);
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid[0], &status[0], 0);
	waitpid(pid[1], &status[1], 0);
	data->exit_status = get_final_status(status);
	return (data->exit_status);
}
