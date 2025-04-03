/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelnyk <dmelnyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:40:13 by dmelnyk           #+#    #+#             */
/*   Updated: 2025/03/12 12:01:22 by dmelnyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./enviroment_private.h"

t_env	*env_get_bykey(t_env *head, char *key)
{
	while (head)
	{
		if (!ft_strcmp(head->key, key))
			return (head);
		head = head->next;
	}
	return (NULL);
}

char	*env_get_value(t_env *head, char *key)
{
	t_env	*temp;

	temp = env_get_bykey(head, key);
	if (temp)
		return (temp->value);
	return (NULL);
}

char	*env_get_key(const char *s)
{
	const char	*anch;

	if (!s || !*s)
		return (NULL);
	if (*s == '$')
		s++;
	if (!ft_isalpha(*s) && *s != '_' && *s != '?')
		return (NULL);
	if (*s == '?')
		return (ft_strdup("?"));
	anch = s;
	while (*s && (ft_isalpha(*s) || ft_isdigit(*s) || *s == '_'))
		s++;
	return (ft_strndup(anch, s - anch));
}

char	**env_create_arr(t_env *env)
{
	char	**envp;
	int		i;
	int		size;

	if (!env)
		return (NULL);
	size = env_getsize(env);
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
