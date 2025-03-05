#include "../../inc/exec.h"

static void	increment_shlvl(t_env *shlvl);
static void	fill_env_with_default(t_env **head);

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
	fill_env_with_default(&head);
	return (head);
}

static void	increment_shlvl(t_env *shlvl)
{
	char	*s;
	int		lvl;

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
		fprintf(stderr, "warning: shell level too high, reseting to 1\n");
		lvl = 1;
	}
	else if (s)
		lvl = 1;
	free(shlvl->value);
	shlvl->value = ft_itoa(lvl);
}

static void	fill_env_with_default(t_env **head)
{
	if (!getenv_val(*head, "PWD"))
		append_env(head, ft_strdup("PWD"), get_curent_dir());
	if (!getenv_val(*head, "SHLVL"))
		append_env(head, ft_strdup("SHLVL"), ft_strdup("1"));
	else
		increment_shlvl(getenv_val(*head, "SHLVL"));
	// TODO:
	if (!getenv_val(*head, "_"))
		append_env(head, ft_strdup("_"), ft_strdup(""));
}
