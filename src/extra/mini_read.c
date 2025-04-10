/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_read.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelnyk <dmelnyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 18:24:29 by dmelnyk           #+#    #+#             */
/*   Updated: 2025/04/07 18:24:30 by dmelnyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "extra_private.h"
#include <signal.h>
#include <readline/readline.h>
#include <sys/ioctl.h>

static inline bool	is_there_missing_char(t_read_state *state, char *line);
static inline void	print_eol_error(t_read_state *state);

static void	signal_handler(int signo)
{
	rl_done = 1;
	rl_erase_empty_line = 1;
	rl_replace_line("", 0);
	ioctl(0, TIOCSTI, "\n");
	rl_on_new_line();
	set_signal(signo);
}

char	*mini_readline(char *prompt, bool complete_state)
{
	t_read_state	st;
	char			*temp;

	signal(SIGINT, signal_handler);
	ft_bzero(&st, sizeof(t_read_state));
	while (1)
	{
		st.cont = readline(prompt);
		rl_erase_empty_line = 0;
		if (get_signal() == SIGINT || !st.cont || !complete_state)
			break ;
		temp = join_strings(3, st.line, "\n", st.cont);
		free(st.line);
		st.line = temp;
		if (!is_there_missing_char(&st, st.cont))
			break ;
		prompt = "> ";
	}
	signal(SIGINT, SIG_IGN);
	if (get_signal() == SIGINT)
		free(st.cont);
	print_eol_error(&st);
	if (!complete_state && get_signal() != SIGINT)
		return (st.cont);
	return (st.line);
}

static inline bool	is_there_missing_char(t_read_state *state, char *line)
{
	int				i;

	if (!line)
		return (0);
	i = -1;
	while (line[++i])
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
	}
	free(state->cont);
	state->cont = NULL;
	return (state->in_squote || state->in_dquote || state->in_parentheses > 0);
}

static inline void	print_eol_error(t_read_state *state)
{
	if (state->in_dquote)
		ft_fprintf(STDERR_FILENO, "unexpected EOF "
			"while looking for matching '\"'\n");
	else if (state->in_squote)
		ft_fprintf(STDERR_FILENO, "unexpected EOF "
			"while looking for matching '''\n");
	else if (state->in_parentheses)
		ft_fprintf(STDERR_FILENO, "unexpected EOF "
			"while looking for matching ')'\n");
}
