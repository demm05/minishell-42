/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelnyk <dmelnyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 22:26:04 by riyano            #+#    #+#             */
/*   Updated: 2025/04/07 18:24:51 by dmelnyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H

typedef struct s_data	t_data;

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
