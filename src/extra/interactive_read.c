#include "./extra_private.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>

static inline bool	is_empty(char *line);

void	interactive_read(t_data *data)
{
	while (1)
	{
		data->line = mini_readline(data->prompt, 1);
		if (get_signal() == SIGINT)
		{
    		set_signal(0);
			data->exit_status = 130;
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
