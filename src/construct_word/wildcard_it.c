/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_it.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelnyk <dmelnyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 17:24:22 by dmelnyk           #+#    #+#             */
/*   Updated: 2025/03/22 19:10:39 by dmelnyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "const_word_private.h"
#include <dirent.h>
#include <stdio.h>

static int	get_size(char *pwd)
{
	DIR				*dir;
    struct dirent	*entry;
    int				size;

	size = 0;
	dir = opendir(pwd);
    if (!dir)
    {
        perror("opendir");
        return (-1);
    }
    while (1)
    {
		entry = readdir(dir);
		if (entry == NULL)
			break ;
		size++;
    }
    closedir(dir);
	return (size);
}

t_token	**wildcard_it(t_token *head)
{
	t_token	**res;
	int		size;

	size = get_size(".");
	if (size == -1)
		return (NULL);
	if (size <= 1)
		res = malloc(sizeof(t_token *) * 2);
	else
		res = malloc(sizeof(t_token *) * (size + 1));
	res[0] = head;
	res[1] = NULL;
	return (res);
}
