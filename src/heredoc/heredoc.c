/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riyano <riyano@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 17:23:41 by riyano            #+#    #+#             */
/*   Updated: 2025/03/28 17:28:42 by riyano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <unistd.h>
#include "./heredoc_private.h"

static inline void	enter_heredoc(char *del, int fd);
static inline bool	remove_quotes(char *s);
static inline char	*expand_line(char *line);

char	*heredoc(t_data *data, char *del)
{
	char	*filename;
	int		fd;

	filename = NULL;
	fd = tmp_new(data->tmp, &filename);
	if (fd == -1)
	{
		perror("tmpfile");
		free(filename);
		return (NULL);
	}
	enter_heredoc(del, fd);
	close(fd);
	return (filename);
}

static inline void	enter_heredoc(char *del, int fd)
{
	bool	expand;	
	bool	escape;
	char	*line;

	expand = remove_quotes(del);
	escape = 0;
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			fprintf(stderr, "warning: here-document delimeted by end-of-file (wanted `%s')", del);
			break ;
		}
		if (!ft_strcmp(del, line))
		{
			free(line);
			break ;
		}
		if (expand)
			line = expand_line(line);
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
}

static inline char	*expand_line(char *line)
{
	return (line);
}

static inline bool	remove_quotes(char *s)
{
	bool	is_quote;
	int		read_index;
	int		write_index;

	is_quote = 0;
	read_index = 0;
	write_index = 0;
	while (s[read_index])
	{
		if (s[read_index] != '\'' && s[read_index] != '"')
			s[write_index++] = s[read_index];
		else
			is_quote = 1;
		read_index++;
	}
	s[write_index] = 0;
	return (is_quote);
}
