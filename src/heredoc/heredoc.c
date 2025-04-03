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

#include <readline/readline.h>
#include <signal.h>
#include "heredoc_private.h"

static inline void	enter_heredoc(t_data *data, char *del, int fd);
static inline bool	remove_quotes(char *s);
static inline void	process_line(t_data *data, int fd, char *s);

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
	enter_heredoc(data, del, fd);
	close(fd);
	if (get_signal() != SIGINT)
		return (filename);
	free(filename);
	set_signal(0);
	return (NULL);
}

static inline void	enter_heredoc(t_data *data, char *del, int fd)
{
	bool	expand;	
	char	*line;

	expand = !remove_quotes(del);
	while (1)
	{
		line = mini_readline("> ", 0);
		if (!line && get_signal() != SIGINT)
			fprintf(stderr, "warning: here-document delimeted by end-of-file (wanted `%s')\n", del);
		if (!line)
			break ;
		if (!ft_strcmp(del, line))
		{
			free(line);
			break ;
		}
		if (expand)
			process_line(data, fd, line);
		else
			write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
}

static inline int	expand_var(t_data *data, int fd, const char *s)
{
	t_env	*e;
	char	*k;
	int		size;

	size = 1;
	k = getenv_key(s);
	if (!k)
		return (write(fd, s, 1));
	size += ft_strlen(k);
	if (*k == '?')
		ft_putnbr_fd(data->exit_status, fd);
	else
	{
		e = env_get_bykey(data->env, k);
		if (e)
			write(fd, e->value, ft_strlen(e->value));
	}
	free(k);
	return (size);
}

static inline void	process_line(t_data *data, int fd, char *s)
{
	int		read_index;

	read_index = 0;
	while (s[read_index])
	{
		if (s[read_index] == '\\')
		{
			if (s[read_index + 1] == '$' || s[read_index + 1] == '\\')
			{
				write(fd, s + 1 + read_index, 1);
				read_index += 2;
			}
			else
				write(fd, s + read_index++, 1);
		}
		else if (s[read_index] == '$')
			read_index += expand_var(data, fd, s + read_index);
		else
			write(fd, s + read_index++, 1);
	}
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
