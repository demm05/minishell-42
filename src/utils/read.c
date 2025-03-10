/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelnyk <dmelnyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 16:17:53 by dmelnyk           #+#    #+#             */
/*   Updated: 2025/03/10 16:18:32 by dmelnyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"
#include "../../inc/exec.h"

bool	is_there_missing_char(t_quote_state *state, char *line);
char	*read_full_line(t_quote_state *state, char *default_prompt);
char	*join(char *s1, char *s2);

volatile bool	g_sig = 0;

void	handle_sigin(int sig)
{
	(void)sig;
	g_sig = 1;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

char	*mini_read(char *prompt)
{
	char			*line;
	t_quote_state	state;

	signal(SIGINT, handle_sigin);
	while (1)
	{
		bzero(&state, sizeof(t_quote_state));
		line = read_full_line(&state, prompt);
		if (!line)
			return (NULL);
		if (!*line)
		{
			free(line);
			continue ;
		}
		if (state.in_double_quote)
			fprintf(stderr, "unexpected EOF while looking for matching '\"'\n");
		else if (state.in_single_quote)
			fprintf(stderr, "unexpected EOF while looking for matching '''\n");
		else if (state.in_parentheses)
			fprintf(stderr, "unexpected EOF while looking for matching ')'\n");
		break ;
	}
	add_history(line);
	signal(SIGINT, SIG_DFL);
	return (line);	
}

char	*read_full_line(t_quote_state *state, char *default_prompt)
{
	char	*old_line;
    char	*continuation;
	char	*line;
	char	*prompt;

	old_line = NULL;
	prompt = default_prompt;
	while (1)
	{
		continuation = readline(prompt);
		if (g_sig)
		{
			bzero(state, sizeof(t_quote_state));
			free(old_line);
			old_line = NULL;
			prompt = default_prompt;
			g_sig = 0;
		}
		else if (!continuation)
			return (line);
		else if (!*continuation)
		{
		free(continuation);
		continue;
		}
		line = join(old_line, continuation);
		free(old_line);
		old_line = line;
		if (!is_there_missing_char(state, continuation))
			break ;
		else
			prompt = "> ";
		free(continuation);
	}
	free(continuation);
	return (line);
}

char	*join(char *s1, char *s2)
{
	char	*res;
	int		s1_l;
	int		s2_l;
	int		i;
	int		j;
	
	i = 0;
	if (s1)
		s1_l = ft_strlen(s1);
	else
		s1_l = 0;
	if (s2)
		s2_l = ft_strlen(s2);
	else
		s2_l = 0;
	res = malloc(sizeof(char) * (s1_l + s2_l + 2));
	if (!res)
	{
		free(s1);
		free(s2);
		exit(1);
	}
	j = 0;
	while (j < s1_l)
		res[i++] = s1[j++];
	res[i++] = '\n';
	j = 0;
	while (j < s2_l)
		res[i++] = s2[j++];
	res[i] = 0;
	return (res);
}

bool is_there_missing_char(t_quote_state *state, char *line)
{
	int				i;

	if (!line)
		return (0);
	i = 0;
	while (line[i])
	{
		if (state->escape)
			state->escape = false;
		else if (line[i] == '\\' && state->in_double_quote)
			state->escape = true;
		else if (line[i] == '\'' && !state->in_double_quote)
			state->in_single_quote = !state->in_single_quote;
		else if (line[i] == '"' && !state->in_single_quote)
			state->in_double_quote = !state->in_double_quote;
		else if (line[i] == '(' && !state->in_double_quote && !state->in_single_quote)
			state->in_parentheses++; 
		else if (line[i] == ')' && !state->in_double_quote && !state->in_single_quote)
			if (state->in_parentheses > 0)
				state->in_parentheses--; 
		i++;
	}
	return (state->in_single_quote || state->in_double_quote || state->in_parentheses > 0);
}
