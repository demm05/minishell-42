/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riyano <riyano@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 22:26:04 by riyano            #+#    #+#             */
/*   Updated: 2025/03/28 22:29:57 by riyano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H

# include "../../inc/minishell.h"

typedef struct s_tmp
{
	unsigned int	*files;
	int				file_count;
	int				arr_size;
	char			*tmpdir;
}	t_tmp;

char	*heredoc(t_data *data, char *del);
t_tmp	*tmp_alloc(void);
void	tmp_del(t_tmp *t);

#endif
