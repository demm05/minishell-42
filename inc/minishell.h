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

// here_doc and missing quote is very simmiliar so it's combined
typedef struct s_here_doc
{
	char	*prompt;
	char	*key;
	bool	expansion;
	bool	missing_quote;
}	t_here_doc;

typedef struct s_data
{
	char		*prompt;
	t_lexer		*l;
	t_astnode	*head;
}	t_data;

#endif
