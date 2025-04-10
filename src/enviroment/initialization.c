/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelnyk <dmelnyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 18:21:06 by dmelnyk           #+#    #+#             */
/*   Updated: 2025/04/07 18:23:12 by dmelnyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "enviroment_private.h"

static void	fill_env_with_default(char **argv, t_env **head);

t_env	*env_init(char **argv, char **envp)
{
	t_env	*head;
	char	*c;
	char	*key;
	int		i;

	if (!envp)
		return (NULL);
	i = -1;
	head = NULL;
	while (envp[++i])
	{
		c = ft_strchr(envp[i], '=');
		if (!c)
			env_append(&head, ft_strdup(envp[i]), ft_strdup(""));
		else
		{
			*c = 0;
			key = ft_strdup(envp[i]);
			*c = '=';
			env_append(&head, key, ft_strdup(++c));
		}
	}
	fill_env_with_default(argv, &head);
	return (head);
}

void	increment_shlvl(t_env *shlvl)
{
	char	*s;
	int		lvl;

	if (!shlvl)
		return ;
	lvl = 0;
	s = shlvl->value;
	if (*s == '+')
		s++;
	while (*s && ft_isdigit(*s) && lvl < 999)
		lvl = lvl * 10 + (*s++ - '0');
	if (*s == '-')
		lvl = 0;
	else if (lvl >= 999)
	{
		ft_fprintf(STDERR_FILENO, "warning: shell level "
			"too high, reseting to 1\n");
		lvl = 1;
	}
	else if (*s)
		lvl = 1;
	else
		lvl++;
	free(shlvl->value);
	shlvl->value = ft_itoa(lvl);
}

/**
 * Fills the environment with default variables if they don't already exist
 * 
 * Sets up essential shell environment variables:
 * - PWD: Current working directory (from get_curent_dir())
 * - SHLVL: Shell level (set to 1 or incremented if exists)
 * - _: Last executed command (initialized to empty string)
 *
 * @param head Double pointer to the head of the environment list
 */
static void	fill_env_with_default(char **argv, t_env **head)
{
	t_env	*pwd;
	char	*s;

	pwd = env_get_bykey(*head, "PWD");
	if (!pwd)
		pwd = env_append(head, ft_strdup("PWD"), get_curent_dir());
	if (!env_get_bykey(*head, "SHLVL"))
		env_append(head, ft_strdup("SHLVL"), ft_strdup("1"));
	else
		increment_shlvl(env_get_bykey(*head, "SHLVL"));
	if (!env_get_bykey(*head, "_"))
	{
		s = ft_strjoin(pwd->value, "/");
		env_append(head, ft_strdup("_"), ft_strjoin(s, argv[0]));
		free(s);
	}
}
