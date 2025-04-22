/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dirs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelnyk <dmelnyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:40:14 by dmelnyk           #+#    #+#             */
/*   Updated: 2025/04/08 17:18:04 by dmelnyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "extra_private.h"
#include <dirent.h>

char	*get_curent_dir(void)
{
	return (getcwd(NULL, 0));
}

static inline int	dir_get_content_size(char *pwd)
{
	int				count;
	DIR				*dir;
	struct dirent	*entry;

	dir = opendir(pwd);
	if (dir == NULL)
	{
		perror("dir_get_content_size: failed to open directory\n");
		return (0);
	}
	count = 0;
	while (1)
	{
		entry = readdir(dir);
		if (entry == NULL)
			break ;
		count++;
	}
	closedir(dir);
	return (count);
}

char	**dir_get_content_list(char *pwd)
{
	DIR				*dir;
	struct dirent	*entry;
	char			**res;
	int				i;
	int				dirs;

	dirs = dir_get_content_size(pwd);
	if (!dirs)
		return (NULL);
	res = malloc(sizeof(char *) * (dirs + 1));
	if (!res)
		return (NULL);
	dir = opendir(pwd);
	i = 0;
	while (i < dirs)
	{
		entry = readdir(dir);
		if (entry == NULL)
			break ;
		res[i++] = ft_strdup(entry->d_name);
	}
	res[i] = NULL;
	closedir(dir);
	return (res);
}

void	dir_free_list(char **l)
{
	int	i;

	if (!l)
		return ;
	i = 0;
	while (l[i])
		free(l[i++]);
	free(l);
}
