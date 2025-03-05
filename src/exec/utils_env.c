#include "../../inc/exec.h"
#include <stdio.h>
#include <string.h>

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
		(*head)->prev->next = new;
		(*head)->prev = new;
	}
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
