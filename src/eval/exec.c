/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelnyk <dmelnyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:40:22 by dmelnyk           #+#    #+#             */
/*   Updated: 2025/03/12 12:46:13 by dmelnyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./eval_private.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>

static char	**build_envp(t_env *env);
static char	**build_args(t_astnode *head);
static char	*get_path(t_env *env, char *literal);
static void	free_envp(char **envp);

bool	handle_exec(t_astnode *head, t_data *data)
{
	int		pid;
	int		status;
	char	*path;
	char	**envp;
	char	**args;

	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		envp = build_envp(data->env);
		args = build_args(head);
		path = get_path(getenv_val(data->env, "PATH"), head->literal);
		args[0] = path;
		execve(path, args, envp);
		puts("child");
		exit(127);
	}
	else
		waitpid(pid, &status, 0);
	data->exit_status = status >> 8;
	if (status)
		return (1);
	return (0);
}

static char	*get_path(t_env *env, char *literal)
{
	char	**dir;
	char	*path;
	char	*temp_path;
	int		len;
	int		i, k;
	int		dir_len;

	path = NULL;
	len = 0;
	if (literal && (literal[0] == '/' || ft_strncmp(literal, "./", 2) == 0))
		path = ft_strdup(literal);
	else if (literal && access(literal, X_OK) == 0)
		path = ft_strdup(literal);
	else if (!env || !*env->value)
		dir = ft_split("usr/bin:/bin", ':');
	else
		dir = ft_split(env->value, ':');
	if (!path)
	{
		if (literal)
			len = ft_strlen(literal);
		i = 0;
		while (dir[i])
		{
			if (!path)
			{
				dir_len = ft_strlen(dir[i]);
				temp_path = malloc(sizeof(char) * (dir_len + len + 2));	
				int	j = 0;
				k = 0;
				while (k < dir_len)
					temp_path[j++] = dir[i][k++];
				temp_path[j++] = '/';
				k = 0;
				while (k < len)
					temp_path[j++] = literal[k++];
				temp_path[j] = 0;
				if (access(temp_path, X_OK) == 0)
					path = temp_path;
				else
					free(temp_path);
			}
			free(dir[i++]);
		}
		free(dir);
	}
	// TODO: check for execution right and if it's directory
	return (path);
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

/*
 * Builds an environment variable array suitable for use with execve.
 * Takes a linked list of environment variables ('t_env') and converts it
 * into a dynamically allocated, NULL-terminated array of strings, where each
 * string is in the format "key=value".
 *
 * - Iterates through the 't_env' list to determine the number of environment variables.
 * - Allocates memory for the resulting array of char pointers (plus a NULL terminator).
 * - Iterates through the 't_env' list again, creating a new string for each
 *   key-value pair.  Each string is allocated enough space for the key,
 *   the '=', the value, and a null terminator.
 * - Copies the key, '=', and value into the newly allocated string.
 * - Sets the last element of the array to NULL.
 * - Handles allocation failures by freeing any previously allocated memory and returning NULL.
 * - Returns NULL if the input 'env' is NULL.
 */
static char	**build_envp(t_env *env)
{
	char	**envp;
	t_env	*penv;
	int		key_size;
	int		value_size;
	int		i;
	int		size;
	int		k;

	if (!env)
		return (NULL);
	penv = env;
	size = 0;
	while (env)
	{
		size++;
		env = env->next;
	}
	envp = malloc((size + 1) * sizeof(char *));
	if (!envp)
		return (NULL);
	env = penv;
	i = -1;
	while (++i < size)
	{
		key_size = ft_strlen(env->key);	
		value_size = ft_strlen(env->value);	
		envp[i] = malloc(key_size + value_size + 2);
		if (!envp[i])
		{
			while (i > 0)
				free(envp[--i]);
			free(envp);
			return (NULL);
		}
		int	j = 0;
		k = 0;
		while (k < key_size)
			envp[i][j++] = env->key[k++];
		envp[i][j++] = '=';
		k = 0;
		while (k < value_size)
			envp[i][j++] = env->value[k++];
		envp[i][j] = 0;
		env = env->next;
	}
	envp[size] = NULL;
	return (envp);
}
