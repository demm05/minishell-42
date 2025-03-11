/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_read_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelnyk <dmelnyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:35:57 by dmelnyk           #+#    #+#             */
/*   Updated: 2025/03/11 17:26:42 by dmelnyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./utils.h"

static char	*join(char *s1, char *s2);
static bool	is_there_missing_char(t_quote_state *state, char *line);

volatile sig_atomic_t	g_signal;

static void	sigint_handler(int sig)
{
	g_signal = sig;
	close(STDIN_FILENO);
}

void	read_full_line(t_data *data, t_quote_state *state)
{
	char	*prompt;
	char	*old_line;
	char	*continuation;

	old_line = NULL;
	prompt = data->prompt;
	g_signal = 0;
	signal(SIGINT, sigint_handler);
	while (1)
	{
		continuation = readline(prompt);
		if (g_signal == SIGINT)
			data->signal = SIGINT;
		if (!continuation)
			return ;
		data->line = join(old_line, continuation);
		free(old_line);
		old_line = data->line;
		if (!is_there_missing_char(state, continuation) || !data->line)
			break ;
		prompt = "> ";
		free(continuation);
	}
	free(continuation);
}

static int	s_len(char *s)
{
	char	*anch;

	if (!s)
		return (0);
	anch = s;
	while (*s)
		s++;
	return (s - anch);
}

static char	*join(char *s1, char *s2)
{
	char	*res;
	int		len_s1;
	int		len_s2;

	len_s1 = s_len(s1);
	len_s2 = s_len(s2);
	res = malloc(sizeof(char) * len_s2 + len_s1 + 2);
	if (!res)
		return (NULL);
	if (s1)
	{
		ft_memcpy(res, s1, len_s1);
		res[len_s1] = '\n';
		ft_memcpy(res + len_s1 + 1, s2, len_s2);
		res[len_s1 + len_s2 + 1] = 0;
	}
	else
	{
		ft_memcpy(res, s2, len_s2);
		res[len_s2] = 0;
	}
	return (res);
}

static bool	is_there_missing_char(t_quote_state *state, char *line)
{
	int				i;

	if (!line)
		return (0);
	i = 0;
	while (line[i])
	{
		if (state->escape)
			state->escape = false;
		else if (line[i] == '\\' && state->in_dquote)
			state->escape = true;
		else if (line[i] == '\'' && !state->in_dquote)
			state->in_squote = !state->in_squote;
		else if (line[i] == '"' && !state->in_squote)
			state->in_dquote = !state->in_dquote;
		else if (line[i] == '(' && !state->in_dquote && !state->in_squote)
			state->in_parentheses++;
		else if (line[i] == ')' && !state->in_dquote && !state->in_squote)
			if (state->in_parentheses > 0)
				state->in_parentheses--;
		i++;
	}
	return (state->in_squote || state->in_dquote || state->in_parentheses > 0);
}
