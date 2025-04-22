/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelnyk <dmelnyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 15:44:19 by dmelnyk           #+#    #+#             */
/*   Updated: 2025/04/02 17:57:12 by riyano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./eval_private.h"
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>

static char	**build_args(t_astnode *head);
static void	free_ptp(char **args);
static void	hangle_failed_execve(t_data *data, char **args,
				char **envp, char *path);

void	exec_command(t_astnode *head, t_data *data)
{
	char	**envp;
	char	**args;
	char	*path;

	if (!*head->literal)
		exit(0);
	data->is_child_proc = 1;
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	path = get_path(env_get_value(data->env, "PATH"), head->literal, data);
	if (!path)
		exit(free_everything(data));
	args = build_args(head);
	env_add(&data->env, "PWD", get_curent_dir());
	env_add(&data->env, "_", path);
	envp = env_create_arr(data->env);
	args[0] = head->literal;
	execve(path, args, envp);
	hangle_failed_execve(data, args, envp, path);
}

static void	hangle_failed_execve(t_data *data, char **args,
				char **envp, char *path)
{
	int	st;

	args[0] = NULL;
	free_ptp(args);
	free_ptp(envp);
	st = path_check_errno(path);
	if (errno == ENOEXEC)
	{
		ft_fprintf(STDERR_FILENO, "%s: Permission denied\n", path);
		data->exit_status = 126;
	}
	else if (st)
		data->exit_status = st;
	else
		data->exit_status = 127;
	exit(free_everything(data));
}

/*
 * Builds an argument array for execve.  Currently incomplete, but intended
 * to function similarly to build_envp.  It will likely traverse the AST
 * rooted at 'head' to construct a NULL-terminated array of strings.
 * Returns NULL for now, but will eventually return the 
 * 		constructed array, or NULL on failure.
 */
static char	**build_args(t_astnode *head)
{
	t_astnode	*child;
	char		**args;
	int			i;

	if (!head)
		return (NULL);
	args = malloc((head->childs + 2) * sizeof(char *));
	if (!args)
		return (NULL);
	ft_bzero(args, (head->childs + 2) * sizeof(char *));
	i = 1;
	child = head->children;
	while (child && i - 1 < head->childs)
	{
		args[i++] = child->literal;
		child = child->next;
	}
	args[i] = NULL;
	return (args);
}

static void	free_ptp(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		free(args[i++]);
	free(args);
}
