/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelnyk <dmelnyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 17:47:54 by dmelnyk           #+#    #+#             */
/*   Updated: 2025/04/09 17:47:54 by dmelnyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "extra_private.h"

static inline void	put_to_str(char *dest, char *src, int *i)
{
	int	j;

	if (!src)
		return ;
	j = 0;
	while (src[j] && *i < PATH_MAX)
	{
		dest[*i] = src[j++];
		*i += 1;
	}
}

static inline void	put_directory(t_data *data, int *i)
{
	char	*wd;
	char	*rr;

	wd = get_curent_dir();
	if (!wd)
		return ;
	put_to_str(data->prompt, GREEN, i);
	rr = ft_strrchr(wd, '/');
	if (rr)
		put_to_str(data->prompt, rr + 1, i);
	else
		put_to_str(data->prompt, wd, i);
	put_to_str(data->prompt, RESET, i);
	free(wd);
}

void	update_prompt(t_data *data)
{
	char	*status;
	int		i;

	i = 0;
	put_directory(data, &i);
	if (data->exit_status)
	{
		status = ft_itoa(data->exit_status);
		put_to_str(data->prompt, RED, &i);
		put_to_str(data->prompt, " [", &i);
		put_to_str(data->prompt, status, &i);
		data->prompt[i++] = ']';
		put_to_str(data->prompt, RESET, &i);
		free(status);
	}
	put_to_str(data->prompt, " > ", &i);
	data->prompt[i] = 0;
}
