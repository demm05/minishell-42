#include "../../inc/exec.h"

bool	handle_export(t_astnode *head, t_data *data)
{
	return (0);
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

t_env	*init_env(char **envp)
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
			append_env(&head, ft_strdup(envp[i]), ft_strdup(""));
		else
		{
			*c = 0;
			key = ft_strdup(envp[i]);
			*c = '=';
			append_env(&head, key, ft_strdup(++c));
		}
	}
	return (head);
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
