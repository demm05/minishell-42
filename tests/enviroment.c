#include "../inc/test.h"
# include <stdarg.h>

t_env	*env = NULL;
t_env	*temp = NULL;
char	**envp = NULL;

void	create_env(int size, ...);
void	free_envp(void);
void	my_free(void)
{
	free_env(&env);
	free_envp();
}

Test(init_env, shlvl_test1, .fini=my_free)
{
	char	*argv[] = {"./minishell"};

	create_env(1, "SHLVL=10");
	env = init_env(argv, envp);
	cr_assert_not_null(env);
	temp = getenv_val(env, "SHLVL"); 
	cr_assert_not_null(temp);
	cr_expect(atoi(temp->value) == 11, "Expected SHLVL 11 != %d", atoi(temp->value));
}

Test(init_env, shlvl_test2, .fini=my_free)
{
	char	*argv[] = {"./minishell"};

	create_env(1, "SHLVL=-19");
	env = init_env(argv, envp);
	cr_assert_not_null(env);
	temp = getenv_val(env, "SHLVL"); 
	cr_assert_not_null(temp);
	cr_expect(atoi(temp->value) == 0, "Expected SHLVL -10 != %d", atoi(temp->value));
}

Test(init_env, shlvl_test3, .fini=my_free)
{
	char	*argv[] = {"./minishell"};

	create_env(1, "SHLVL=998");
	env = init_env(argv, envp);
	cr_assert_not_null(env);
	temp = getenv_val(env, "SHLVL"); 
	cr_assert_not_null(temp);
	cr_expect(atoi(temp->value) == 999, "Expected SHLVL 999 != %d", atoi(temp->value));
}

Test(init_env, shlvl_test4, .fini=my_free)
{
	char	*argv[] = {"./minishell"};

	create_env(1, "SHLVL=999");
	cr_redirect_stderr();
	env = init_env(argv, envp);
	cr_assert_stderr_eq_str("warning: shell level too high, reseting to 1\n");
	cr_assert_not_null(env);
	temp = getenv_val(env, "SHLVL"); 
	cr_assert_not_null(temp);
	cr_expect(atoi(temp->value) == 1, "Expected SHLVL (999 -> 1) != %d", atoi(temp->value));
}

Test(empty_env, init_env_test_1, .fini=my_free)
{
	char	*cd;
	char	*argv[] = {"./minishell"};

	create_env(0);
	env = init_env(argv, envp);
	cr_assert_not_null(env);
	cr_assert_not_null(getenv_val(env, "SHLVL"));
	cr_expect(atoi(getenv_val(env, "SHLVL")->value) == 1);
	cr_assert_not_null(getenv_val(env, "_"));
	cr_assert_not_null(getenv_val(env, "PWD"));
	cd = get_curent_dir();
	cr_expect(strcmp(getenv_val(env, "PWD")->value, cd) == 0);
	free(cd);
}

void	create_env(int size, ...)
{
	char	*s;
	va_list	args;
	int		i;

	va_start(args, size);
	envp = malloc(sizeof(char *) * (size + 1));
	i = 0;
	while (i < size)
	{
		s = va_arg(args, char *);
		envp[i++] = ft_strdup(s);
	}
	va_end(args);
	envp[i] = NULL;
}

void	free_envp(void)
{
	int	i;

	if (!envp)
		return ;
	i = 0;
	while (envp[i])
		free(envp[i++]);
	free(envp);
	envp = NULL;
}
