/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactive_read.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelnyk <dmelnyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 18:24:24 by dmelnyk           #+#    #+#             */
/*   Updated: 2025/04/07 18:24:24 by dmelnyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./extra_private.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>

static inline bool	is_empty(char *line);

char *generate_prompt(int exit_status)
{
	char	cwd[PATH_MAX];
	char	*base;
	char	*prompt;
	char	*tmp;
	char	*status;

	prompt = malloc(512);
	if (!prompt)
		return NULL;
	prompt[0] = '\0';
	if (!getcwd(cwd, sizeof(cwd)))
		ft_strlcpy(cwd, "unknown", 7);
	base = ft_strrchr(cwd, '/');
	if (base)
		base++;
	else
		base = cwd;
	tmp = join_strings(3, GREEN, base, RESET);
	ft_strlcat(prompt, tmp, 512);
	free(tmp);
	if (exit_status != 0)
	{
		status = ft_itoa(exit_status);
		if (!status)
			return (NULL);
		tmp = join_strings(5, RED, " [", status, "]", RESET);
		free(status);
		ft_strlcat(prompt, tmp, 512);
		free(tmp);
	}
	ft_strlcat(prompt, " > ", 512);
	return (prompt);
}

void	update_prompt(t_data *data)
{
	char	*new_prompt;

	new_prompt = generate_prompt(data->exit_status);
	if (!new_prompt)
	{
		perror("malloc");
		return ;
	}
	if (data->prompt)
	{
		free(data->prompt);
		data->prompt = NULL;
	}
	data->prompt = new_prompt;
}

void	interactive_read(t_data *data)
{
	update_prompt(data);
	while (1)
	{
		data->line = mini_readline(data->prompt, 1);
		if (get_signal() == SIGINT)
		{
			set_signal(0);
			data->exit_status = 130;
			update_prompt(data);
			continue ;
		}
		else if (!data->line)
			return ;
		if (is_empty(data->line))
		{
			free(data->line);
			continue ;
		}
		break ;
	}
	add_history(data->line);
}

static bool	is_empty(char *s)
{
	int		read_index;
	int		write_index;
	bool	sp;

	read_index = 0;
	write_index = 0;
	sp = 1;
	while (s[read_index])
	{
		if (!ft_isspace(s[read_index]))
			sp = 0;
		if (!sp)
			s[write_index++] = s[read_index];
		read_index++;
	}
	s[write_index] = 0;
	return (*s == 0);
}
