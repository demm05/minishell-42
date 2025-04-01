/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelnyk <dmelnyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 15:51:03 by dmelnyk           #+#    #+#             */
/*   Updated: 2025/03/12 11:36:39 by dmelnyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <sys/wait.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>

static int	g_signal = 0;

void	set_signal(int sig)
{
	g_signal = sig;
}

int	get_signal(void)
{
	return (g_signal);
}

void	reset_signals(void)
{
	signal(SIGINT, SIG_DFL);
}

int	get_childs_status(int status)
{
	if (WCOREDUMP(status))
		return (131);
	else if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		return (130);
	return (WEXITSTATUS(status));
}
