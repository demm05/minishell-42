/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelnyk <dmelnyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:40:13 by dmelnyk           #+#    #+#             */
/*   Updated: 2025/03/12 12:01:22 by dmelnyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./enviroment_private.h"

t_env	*env_append(t_env **head, char *key, char *value)
{
	t_env	*new;

	if (!head)
		return (NULL);
	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->next = NULL;
	new->key = key;
	new->value = value;
	if (!*head)
	{
		new->prev = new;
		*head = new;
	}
	else
	{
		new->prev = (*head)->prev;
		(*head)->prev->next = new;
		(*head)->prev = new;
	}
	return (new);
}

t_env	*env_add(t_env **head, char *key, char *value)
{
	t_env	*new;

	if (!head)
		return (NULL);
	new = env_get_bykey(*head, key);
	if (!new)
		return (env_append(head, ft_strdup(key), value));
	free(new->value);
	new->value = value;
	return (new);
}

void	env_free(t_env **head)
{
	t_env	*cur;
	t_env	*next;

	if (!head)
		return ;
	cur = *head;
	while (cur)
	{
		next = cur->next;
		free(cur->key);
		free(cur->value);
		free(cur);
		cur = next;
	}
	*head = NULL;
}

void	env_unset(t_env **env, char *kk)
{
	t_env	*prev;
	t_env	*next;
	t_env	*key;

	if (!env || !*env || !kk)
		return ;
	key = env_get_bykey(*env, kk);
	if (!key)
		return ;
	prev = key->prev;
	next = key->next;
	free(key->key);
	free(key->value);
	if (key == *env)
	{
		free(*env);
		*env = next;
		return ;
	}
	free(key);
	if (prev)
		prev->next = next;
	if (!next)
		(*env)->prev = prev;
	else
		next->prev = prev;
}

int	env_getsize(t_env *env)
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
