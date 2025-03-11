/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_read.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelnyk <dmelnyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 16:17:53 by dmelnyk           #+#    #+#             */
/*   Updated: 2025/03/11 17:28:47 by dmelnyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./utils.h"

static void	pritn_eol_error(t_quote_state *state)
{
	if (state->in_dquote)
		fprintf(stderr, "unexpected EOF while looking for matching '\"'\n");
	else if (state->in_squote)
		fprintf(stderr, "unexpected EOF while looking for matching '''\n");
	else if (state->in_parentheses)
		fprintf(stderr, "unexpected EOF while looking for matching ')'\n");
}

static void	handle_sigint(int original_fd, t_quote_state *state,
						bool *newln, t_data *data)
{
	free(data->line);
	data->line = NULL;
	dup2(original_fd, STDIN_FILENO);
	if (!*newln)
	{
		write(STDIN_FILENO, "\n", 1);
		*newln = 1;
	}
	if (state->in_parentheses || state->in_dquote || state->in_squote)
		write(STDIN_FILENO, "\n", 1);
	data->signal = 0;
}

static bool	is_empty(t_data *data)
{
	char	*s;

	if (!data)
		return (1);
	s = data->line;
	if (!s)
		return (1);
	while (*s && ft_isspace(*s))
		s++;
	if (*s)
		return (0);
	free(data->line);
	data->line = NULL;
	return (1);
}

void	mini_read(t_data *data)
{
	t_quote_state	state;
	int				original_fd;
	bool			newln_sigint;

	newln_sigint = 0;
	original_fd = dup(STDIN_FILENO);
	while (1)
	{
		bzero(&state, sizeof(t_quote_state));
		read_full_line(data, &state);
		if (data->signal == SIGINT)
		{
			handle_sigint(original_fd, &state, &newln_sigint, data);
			continue ;
		}
		else if (!data->line)
			return ;
		pritn_eol_error(&state);
		if (is_empty(data))
			continue ;
		break ;
	}
	reset_signals();
	add_history(data->line);
}
