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

void	exec_command(t_astnode *head, t_data *data)
{
	char	**envp;
	char	**args;
	char	*path;

	if (!*head->literal)
		exit(0);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	envp = env_create_arr(data->env);
	args = build_args(head);
	path = get_path(env_get_bykey(data->env, "PATH"), head->literal, data);
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
	free_everything(data);
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
