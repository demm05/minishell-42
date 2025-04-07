/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelnyk <dmelnyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 17:44:58 by riyano            #+#    #+#             */
/*   Updated: 2025/04/07 18:24:32 by dmelnyk          ###   ########.fr       */
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

char	*get_path(t_env *env, char *literal, t_data *data)
{
	char		*path;
	char		**dirs;
	char		*tmp;
	int			i;
	struct stat	st;

	if (ft_strchr(literal, '/'))
		return (check_explicit_path(literal, data));
	if (!env || !env->value || !env->value[0])
		return (NULL);
	dirs = ft_split(env->value, ":");
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
