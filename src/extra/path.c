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

#include "extra_private.h"
#include <sys/stat.h>
#include <errno.h>
#include <string.h>

int	path_check_errno(const char *path)
{
	if (errno == ENONET)
	{
		ft_fprintf(STDERR_FILENO, "%s: No such file or directory\n", path);
		return (127);
	}
	else if (errno == EACCES)
	{
		ft_fprintf(STDERR_FILENO, "%s: Permission denied\n", path);
		return (126);
	}
	return (0);
}

int	check_path_perm(char *path)
{
	struct stat	st;

	if (access(path, F_OK) != 0)
	{
		ft_fprintf(STDERR_FILENO, "%s: No such file or directory\n", path);
		return (127);
	}
	if (stat(path, &st) != 0)
		return (path_check_errno(path));
	if (S_ISDIR(st.st_mode))
	{
		ft_fprintf(STDERR_FILENO, "%s: Is a directory\n", path);
		return (126);
	}
	if (access(path, X_OK) != 0)
	{
		ft_fprintf(STDERR_FILENO, "%s: Permission denied\n", path);
		return (126);
	}
	return (0);
}

static char	*check_explicit_path(char *path, t_data *data)
{
	int	st;

	st = check_path_perm(path);
	if (st)
	{
		data->exit_status = st;
		return (NULL);
	}
	return (ft_strdup(path));
}

static inline char	*handle_return(t_data *data, char *literal, char *path)
{
	int	st;

	if (!path)
	{
		ft_fprintf(STDERR_FILENO, "%s: command not found\n", literal);
		data->exit_status = 127;
		return (NULL);
	}
	st = check_path_perm(path);
	if (st)
	{
		data->exit_status = st;
		free(path);
		return (NULL);
	}
	return (path);
}

char	*get_path(char *env, char *literal, t_data *data)
{
	char		*path;
	char		**dirs;
	char		*tmp;
	int			i;
	struct stat	st;

	if (ft_strchr(literal, '/'))
		return (check_explicit_path(literal, data));
	if (!env || !env[0])
		return (NULL);
	dirs = ft_split(env, ":");
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
	return (handle_return(data, literal, path));
}
