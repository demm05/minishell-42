#include "../../inc/exec.h"

static bool	validate_env_vars(t_env **pwd, t_env **old_pwd, t_data *data);
static bool	perform_chdir(char *path, t_data *data, bool to_free);
static bool	update_pwd_environment(t_env *pwd, t_env *old_pwd);
char		*resolve_cd_path(t_astnode *head, t_env *old_pwd, t_data *data, bool *to_free);
char		*temp_strdup(t_astnode *head);

bool	handle_cd(t_astnode *head, t_data *data)
{
	t_env	*pwd;
	t_env	*old_pwd;
	char	*new_pwd;
	bool	to_free;

	if (!validate_env_vars(&pwd, & old_pwd, data))
		return (1);
	if (head->childs > 1)
	{
		fprintf(stderr, "cd: too many arguments\n");
		data->exit_status = 1;
		return (1);
	}
	new_pwd = resolve_cd_path(head, old_pwd, data, &to_free);
	if (!new_pwd)
		return (1);
	if (!perform_chdir(new_pwd, data, to_free))
		return (1);
	if (!update_pwd_environment(pwd, old_pwd))
	{
		data->exit_status = 1;
		return (1);
	}
	return (0);
}

bool	validate_env_vars(t_env **pwd, t_env **old_pwd, t_data *data)
{
	*pwd = getenv_val(data->env, "PWD");
	*old_pwd = getenv_val(data->env, "OLDPWD");
	if (!*pwd)
		*pwd = append_env(&data->env, ft_strdup("PWD"), get_curent_dir());
	if (!*old_pwd)
		*old_pwd = append_env(&data->env,
				ft_strdup("OLDPWD"), get_curent_dir());
	if (!*pwd || !*old_pwd)
	{
		fprintf(stderr, "cd: failed to set up environment variables\n");
		data->exit_status = 1;
		return (false);
	}
	return (true);
}

char	*resolve_cd_path(t_astnode *head, t_env *old_pwd, t_data *data, bool *to_free)
{
	t_env	*temp;

	*to_free = 0;
	if (head->childs == 0)
	{
		temp = getenv_val(data->env, "HOME");
		if (!temp)
		{
			printf("cd: HOME not set\n");
			data->exit_status = 1;
			return (NULL);
		}
		return (temp->value);
	}
	if (old_pwd->value && *head->children->literal && \
		*head->children->literal == '-')
		return (old_pwd->value);
	*to_free = 1;
	return (temp_strdup(head->children));
}

static bool	perform_chdir(char *path, t_data *data, bool to_free)
{
	if (chdir(path) != 0)
	{
		perror("cd");
		data->exit_status = 1;
		if (to_free)
			free(path);
		return (0);
	}
	if (to_free)
		free(path);
	return (1);
}

static bool	update_pwd_environment(t_env *pwd, t_env *old_pwd)
{
	free(old_pwd->value);
	old_pwd->value = pwd->value;
	pwd->value = get_curent_dir();
	return (pwd->value != NULL);
}

// TODO: DELETE IT UNNECESSARY FUNCTION, BUT FIRST LEXER SHOULD BE MOIDIFIED
char	*temp_strdup(t_astnode *head)
{
	char	*r;

	if (!head)
		return (NULL);
	if (!head->lit_size)
		return (NULL);
	r = malloc(sizeof(char) * (head->lit_size + 1));
	if (!r)
		return (NULL);
	strncpy(r, head->literal, head->lit_size);
	r[head->lit_size] = 0;
	return (r);
}
