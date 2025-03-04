#include "../../inc/exec.h"

bool	handle_env(t_astnode *head, t_data *data)
{
	t_env	*env;

	env = data->env;
	while (env)
	{
		printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
	return (0);
}

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
