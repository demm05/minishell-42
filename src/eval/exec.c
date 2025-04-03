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
#include <sys/wait.h>
#include <sys/ioctl.h>

bool	handle_exec(t_astnode *head, t_data *data)
{
	int		pid;
	int		status;

	if (!*head->literal)
		return (0);
	status = 0;
	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
		exec_command(head, data);
	else
		waitpid(pid, &status, 0);
	data->exit_status = get_childs_status(status);
	return (data->exit_status);
}
