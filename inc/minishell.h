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
	char		*prompt;
	char		*line;
	t_lexer		*l;
	t_astnode	*head;
	t_env		*env;
	int			exit_status;
}	t_data;

typedef struct s_quote_state
{
	bool	escape;
	bool	in_single_quote;
	bool	in_double_quote;
	int		in_parentheses;
}	t_quote_state;


void	exec(t_data *data);
char	*mini_read(char *prompt);

#endif
