/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelnyk <dmelnyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:40:22 by dmelnyk           #+#    #+#             */
/*   Updated: 2025/03/06 13:43:47 by dmelnyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/exec.h"

static char	**build_envp(t_env *env);
static char	**build_args(t_astnode *head);
static void	free_envp(char **envp);

bool	handle_exec(t_astnode *head, t_data *data)
{
	int		pid;
	int		status;
	char	**envp;
	char	**args;

	// Prototype
	/*
	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		envp = build_envp(data->env);
		args = build_args(head->children);
		free_envp(envp);
		execve(head->literal, args, envp);
	}
	else
		waitpid(pid, &status, 0);
	*/
	return (0);
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
	char	**args;

	if (!head)
		return (NULL);
	return (NULL);
}

/*
 * Frees a NULL-terminated array of strings (like the one created by build_envp).
 * Iterates through the array, freeing each individual string, and then frees
 * the array itself.  Handles NULL input gracefully.
 */
static void	free_envp(char **envp)
{
	int	i;

	if (!envp)
		return ;
	i = 0;
	while (envp[i])
		free(envp[i++]);
	free(envp);
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
