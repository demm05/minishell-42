#include "../inc/minishell.h"
#include "../inc/exec.h"

char	*get_path(t_env *env, char *literal)
{
	char	**dir;
	char	*path;
	char	*temp_path;
	int		len;
	int		i, k;
	int		dir_len;

	path = NULL;
	len = 0;
	if (literal && (literal[0] == '/' || ft_strncmp(literal, "./", 2) == 0))
		path = ft_strdup(literal);
	else if (literal && access(literal, X_OK) == 0)
		path = ft_strdup(literal);
	else if (!env || !*env->value)
		dir = ft_split("usr/bin:/bin", ':');
	else
		dir = ft_split(env->value, ':');
	if (!path)
	{
		if (literal)
			len = ft_strlen(literal);
		i = 0;
		while (dir[i])
		{
			if (!path)
			{
				dir_len = ft_strlen(dir[i]);
				temp_path = malloc(sizeof(char) * (dir_len + len + 2));	
				int	j = 0;
				k = 0;
				while (k < dir_len)
					temp_path[j++] = dir[i][k++];
				temp_path[j++] = '/';
				k = 0;
				while (k < len)
					temp_path[j++] = literal[k++];
				temp_path[j] = 0;
				if (access(temp_path, X_OK) == 0)
					path = temp_path;
				else
					free(temp_path);
			}
			free(dir[i++]);
		}
		free(dir);
	}
	// TODO: check for execution right and if it's directory
	return (path);
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;
	char	*path;

	(void)argc;
	env = init_env(argv, envp);
	if (!env)
		return (1);
	path = get_path(getenv_val(env, "PATH"), argv[1]);
	printf("%s\n", path);
	printf("%d\n", access("src/", X_OK));
	if (path)
		free(path);
	free_env(&env);
}
