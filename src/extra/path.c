/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riyano <riyano@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 17:44:58 by riyano            #+#    #+#             */
/*   Updated: 2025/04/02 17:58:35 by riyano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./extra_private.h"
#include <sys/stat.h>

static char	*check_explicit_path(char *literal, t_data *data)
{
	struct stat	st;

	if (access(literal, F_OK) != 0)
	{
		fprintf(stderr, "%s: No such file or directory\n", literal);
		data->exit_status = 127;
		return (NULL);
	}
	if (stat(literal, &st) == 0 && S_ISDIR(st.st_mode))
	{
		fprintf(stderr, "%s: Is a directory\n", literal);
		data->exit_status = 126;
		return (NULL);
	}
	if (access(literal, X_OK) != 0)
	{
		fprintf(stderr, "%s: Permission denied\n", literal);
		data->exit_status = 126;
		return (NULL);
	}
	return (ft_strdup(literal));
}

static char	**get_dirs(t_env *env)
{
	char	**dirs;

	if (!env || !env->value || !env->value[0])
		dirs = ft_split("usr/bin:/bin", ":");
	else
		dirs = ft_split(env->value, ":");
	return (dirs);
}

char	*get_path(t_env *env, char *literal, t_data *data)
{
	char		*path;
	char		**dirs;
	char		*tmp;
	int			i;
	struct stat	st;

	if (ft_strchr(literal, '/'))
		return (check_explicit_path(literal, data));
	dirs = get_dirs(env);
	path = NULL;
	i = 0;
	while (dirs[i] && !path)
	{
		tmp = join_strings(3, dirs[i], "/", literal);
		if (tmp && access(tmp, X_OK) == 0 && stat(tmp, &st) == 0
			&& !S_ISDIR(st.st_mode))
			path = tmp;
		if (!path && tmp)
			free(tmp);
		free(dirs[i++]);
	}
	free(dirs);
	return (path);
}
