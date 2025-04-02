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
#include "../extra/extra.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>

static char	**build_envp(t_env *env);
static char	**build_args(t_astnode *head);

void	exec_command(t_astnode *head, t_data *data)
{
	char	**envp;
	char	**args;
	char	*path;

	if (!*head->literal)
		exit(0);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	envp = build_envp(data->env);
	args = build_args(head);
	path = get_path(getenv_val(data->env, "PATH"), head->literal, data);
	if (!path)
	{
		if (!ft_strchr(head->literal, '/'))
		{
			fprintf(stderr, "%s: command not found\n", head->literal);
			data->exit_status = 127;
		}
		exit(data->exit_status);
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

static int	calc_envsize(t_env *env)
{
	int	size;

	size = 0;
	while (env)
	{
		size++;
		env = env->next;
	}
	return (size);
}

/*
 * Builds an environment variable array suitable for use with execve.
 * Takes a linked list of environment variables ('t_env') and converts it
 * into a dynamically allocated, NULL-terminated array of strings, where each
 * string is in the format "key=value".
 */
static char	**build_envp(t_env *env)
{
	char	**envp;
	int		i;
	int		size;

	if (!env)
		return (NULL);
	size = calc_envsize(env);
	envp = malloc((size + 1) * sizeof(char *));
	if (!envp)
		return (NULL);
	i = -1;
	while (++i < size)
	{
		envp[i] = join_strings(3, env->key, "=", env->value);
		env = env->next;
	}
	envp[size] = NULL;
	return (envp);
}
