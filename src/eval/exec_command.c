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

static char	**build_args(t_astnode *head);
static void	handle_error(char *literal, t_env *path_env, t_data *data);
static void	free_ptp(char **args);

void	exec_command(t_astnode *head, t_data *data)
{
	char	**envp;
	char	**args;
	char	*path;
	t_env	*path_env;

	if (!*head->literal)
		exit(0);
	data->is_child_proc = 1;
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	args = build_args(head);
	path_env = env_get_bykey(data->env, "PATH");
	path = get_path(path_env, head->literal, data);
	env_add(&data->env, "PWD", get_curent_dir());
	env_add(&data->env, "_", path);
	envp = env_create_arr(data->env);
	if (!path)
	{
		free_ptp(args);
		free_ptp(envp);
		handle_error(head->literal, path_env, data);
	}
	args[0] = head->literal;
	execve(path, args, envp);
	exit(127);
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

static void	handle_error(char *literal, t_env *path_env, t_data *data)
{
	int	status;

	if (!ft_strchr(literal, '/'))
	{
		if (!path_env || !path_env->value || !path_env->value[0])
			ft_fprintf(STDERR_FILENO, "%s: No such file or "
				"directory\n", literal);
		else
			ft_fprintf(STDERR_FILENO, "%s: command not found\n", literal);
		data->exit_status = 127;
	}
	status = free_everything(data);
	exit(status);
}

static void	free_ptp(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		free(args[i++]);
	free(args);
}
