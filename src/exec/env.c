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
