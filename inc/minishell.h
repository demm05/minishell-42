#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include "libft.h"
# include "parser/types.h"
# include "exec/types.h"

typedef struct s_data
{
	char					*prompt;
	char					*line;
	t_lexer					*l;
	t_astnode				*head;
	t_env					*env;
	int						exit_status;
	int						signal;
}	t_data;

void	exec(t_data *data);
void	mini_read(t_data *data);
void	reset_signals(void);

#endif
