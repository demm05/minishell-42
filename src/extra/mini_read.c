#include "extra_private.h"
#include <signal.h>
#include <readline/readline.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <unistd.h>

static inline char	*join(char *s1, char *s2);
static inline bool	is_there_missing_char(t_read_state *state);
static inline void	print_eol_error(t_read_state *state);

static inline void	sig_receiver(int sig)
{
	set_signal(sig);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

char	*mini_readline(char *prompt, bool complete_state)
{
	t_read_state	st;

	set_signal(0);
	if (!isatty(fileno(stdin)))
		return (get_next_line(fileno(stdin)));
	signal(SIGINT, sig_receiver);
	ft_bzero(&st, sizeof(t_read_state));
	while (1)
	{
		st.cont = readline(prompt);
		if (get_signal() == SIGINT)
			break ;
		if (!complete_state)
			st.line = st.cont;
		if (!st.cont|| !complete_state)
			break ;
		st.line = join(st.line, st.cont);
		if (!is_there_missing_char(&st))
			break ;
		prompt = "> ";
	}
	if (get_signal() == SIGINT)
		free(st.cont);
	signal(SIGINT, SIG_IGN);
	print_eol_error(&st);
	return (st.line);
}

static inline char	*join(char *s1, char *s2)
{
	char	*res;
	int		len_s1;
	int		len_s2;

	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
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
	free(s1);
	return (res);
}

static inline bool	is_there_missing_char(t_read_state *state)
{
	int				i;
	char			*line;

	line = state->cont;
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
	return (state->in_squote || state->in_dquote || state->in_parentheses > 0);
}

static inline void	print_eol_error(t_read_state *state)
{
	if (state->in_dquote)
		fprintf(stderr, "unexpected EOF while looking for matching '\"'\n");
	else if (state->in_squote)
		fprintf(stderr, "unexpected EOF while looking for matching '''\n");
	else if (state->in_parentheses)
		fprintf(stderr, "unexpected EOF while looking for matching ')'\n");
}
