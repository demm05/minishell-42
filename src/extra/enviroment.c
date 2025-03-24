/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelnyk <dmelnyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:40:13 by dmelnyk           #+#    #+#             */
/*   Updated: 2025/03/12 12:01:22 by dmelnyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "./extra.h"
#include <stdlib.h>

t_env	*getenv_val(t_env *head, char *key)
{
	while (head)
	{
		if (!ft_strcmp(head->key, key))
			return (head);
		head = head->next;
	}
	return (NULL);
}

t_env	*append_env(t_env **head, char *key, char *value)
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

t_env	*add_env(t_env **head, char *key, char *value)
{
	t_env	*new;

	if (!head)
		return (NULL);
	new = getenv_val(*head, key);
	if (!new)
		return (append_env(head, key, value));
	free(new->value);
	new->value = value;
	return (new);
}

void	free_env(t_env **head)
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
	key = getenv_val(*env, kk);
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
	else if (!next)
		(*env)->prev = prev;
}
