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
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <readline/readline.h>
#include "./heredoc.h"

char *generate_filename(void)
{
	char	buf[16];
	int		n;
	int		i;
	char	*res;

	n = 0;
	while (n < 10)
	{
		i = 0;
		while ("heredoc_tmp"[i])
		{
			buf[i] = "heredoc_tmp"[i];
			i++;
		}
		buf[i++] = '0' + n;
		buf[i] = '\0';
		if (access(buf, F_OK) == -1)
		{
			res = malloc(i + 1);
			if (!res)
				return (0);
			n = 0;
			while (n <= i)
			{
				res[n] = buf[n];
				n++;
			}
			return (res);
		}
		n++;
	}
	return (0);
}

#include <string.h>
#include <stdbool.h>

bool	is_quoted(const char *delimiter)
{
    if (ft_strlen(delimiter) >= 2 &&
			((delimiter[0] == '\'' && delimiter[len - 1] == '\'') ||
			(delimiter[0] == '"' && delimiter[len - 1] == '"')))
		return true;
	return false;
}

//TODO:
char	*expand_env_vars(line);

char	*read_heredoc(t_token *head)
{
	char	*line;
	int		fd;
	char	*filename;
	bool	expand_vars;
	char	*delimiter;

	filename = generate_filename();
	if (!filename)
		return (NULL);
	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd < 0)
	{
		perror("open");
		return (NULL);
	}
	expand_vars = true;
	if (is_quoted(head->literal))
	{
		expand_vars = false;
		delimiter = remove_quotes(head->literal);
	}
	else
		delimiter = haed->literal;
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0)
		{
			free(line);
			break ;
		}
		if (expand_vars)
			line = expand_env_vars(line);
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
	return (filename);
}
