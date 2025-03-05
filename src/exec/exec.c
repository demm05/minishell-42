#include "../../inc/exec.h"

static char	**build_envp(t_env *env);
static char	**build_args(t_astnode *head);
void		free_envp(char **envp);

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

static char	**build_args(t_astnode *head)
{
	char	**args;

	if (!head)
		return (NULL);
	return (NULL);
}

void	free_envp(char **envp)
{
	int	i;

	if (!envp)
		return ;
	i = 0;
	while (envp[i])
		free(envp[i++]);
	free(envp);
}

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
