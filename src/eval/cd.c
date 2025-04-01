/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelnyk <dmelnyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:40:39 by dmelnyk           #+#    #+#             */
/*   Updated: 2025/03/12 12:46:02 by dmelnyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./eval_private.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

static bool	validate_env_vars(t_env **pwd, t_env **old_pwd, t_data *data);
static char	*resolve_cd_path(t_astnode *head, t_env *old_pwd, t_data *data);
static bool	perform_chdir(char *path, t_data *data);
static bool	update_pwd_environment(t_env *pwd, t_env *old_pwd);

bool	handle_cd(t_astnode *head, t_data *data)
{
	t_env	*pwd;
	t_env	*old_pwd;
	char	*new_pwd;

	if (!validate_env_vars(&pwd, &old_pwd, data))
		return (1);
	if (head->childs > 1)
	{
		fprintf(stderr, "cd: too many arguments\n");
		data->exit_status = 1;
		return (1);
	}
	new_pwd = resolve_cd_path(head, old_pwd, data);
	if (!new_pwd)
		return (1);
	if (!perform_chdir(new_pwd, data))
		return (1);
	if (!update_pwd_environment(pwd, old_pwd))
	{
		data->exit_status = 1;
		return (1);
	}
	data->exit_status = 0;
	return (0);
}

/**
 * Validates and ensures PWD and OLDPWD environment variables exist
 * 
 * Creates these variables if they don't exist using the current directory.
 *
 * @param pwd Double pointer to store the PWD environment variable
 * @param old_pwd Double pointer to store the OLDPWD environment variable
 * @param data Data structure containing environment and status information
 * @return true if validation succeeds, false if it fails
 */
static bool	validate_env_vars(t_env **pwd, t_env **old_pwd, t_data *data)
{
	*pwd = getenv_val(data->env, "PWD");
	*old_pwd = getenv_val(data->env, "OLDPWD");
	if (!*pwd)
		*pwd = add_env(&data->env, ft_strdup("PWD"), get_curent_dir());
	if (!*old_pwd)
		*old_pwd = add_env(&data->env,
				ft_strdup("OLDPWD"), get_curent_dir());
	if (!*pwd || !*old_pwd)
	{
		fprintf(stderr, "cd: failed to set up environment variables\n");
		data->exit_status = 1;
		return (false);
	}
	return (true);
}

/**
 * Resolves the target path for cd command
 * 
 * Handles cases: no arguments (HOME), "-" (previous directory), 
 * 		and path arguments.
 * Sets to_free flag if memory is allocated for the returned path.
 *
 * @param head AST node containing command arguments
 * @param old_pwd OLDPWD environment variable
 * @param data Data structure containing environment and status
 * @param to_free Pointer to bool that indicates if 
 * 			returned path should be freed
 * @return Target directory path or NULL on error
 */
static char	*resolve_cd_path(t_astnode *head, t_env *old_pwd, t_data *data)
{
	t_env	*temp;

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
	return (head->children->literal);
}

/**
 * Performs the directory change operation
 * 
 * Changes the directory and handles potential errors.
 * Frees the path if to_free is true.
 *
 * @param path Directory path to change to
 * @param data Data structure containing environment and status
 * @param to_free Whether the path should be freed
 * @return true on success, false on failure
 */
static bool	perform_chdir(char *path, t_data *data)
{
	if (chdir(path) != 0)
	{
		fprintf(stderr, "cd: %s: %s\n", path, strerror(errno));
		data->exit_status = 1;
		return (0);
	}
	return (1);
}

/**
 * Updates PWD and OLDPWD environment variables after directory change
 * 
 * Sets OLDPWD to the previous PWD value and
 * updates PWD to the current directory.
 *
 * @param pwd PWD environment variable
 * @param old_pwd OLDPWD environment variable
 * @return true if update succeeds, false if it fails
 */
static bool	update_pwd_environment(t_env *pwd, t_env *old_pwd)
{
	free(old_pwd->value);
	old_pwd->value = pwd->value;
	pwd->value = get_curent_dir();
	return (pwd->value != NULL);
}
