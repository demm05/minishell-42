#include "./extra_private.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <stdlib.h>

static inline bool	is_empty(t_data *data);

void	interactive_read(t_data *data)
{
	while (1)
	{
		data->line = mini_readline(data->prompt, 1);
		if (get_signal() == SIGINT)
		{
			data->exit_status = 130;
			continue ;
		}
		else if (!data->line)
			return ;
		if (is_empty(data))
			continue ;
		break ;
	}
	add_history(data->line);
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
