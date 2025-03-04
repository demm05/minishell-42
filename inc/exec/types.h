#ifndef ETYPES_H
# define ETYPES_H

# include "../parser/types.h"

typedef struct s_data t_data;
typedef bool (*builtin_func_ptr)(t_astnode *head, t_data *data);

// here_doc and missing quote is very simmiliar so it's combined
typedef struct s_here_doc
{
	char	*prompt;
	char	*key;
	bool	expansion;
	bool	missing_quote;
}	t_here_doc;

typedef struct s_env
{
	char	*key;
	char	*value;
	struct s_env	*next;
	struct s_env	*prev;
}	t_env;

void	exec(t_data *data);

// Built in functions for execution
bool	handle_echo(t_astnode *head, t_data *data);
bool	handle_cd(t_astnode *head, t_data *data);
bool	handle_pwd(t_astnode *head, t_data *data);
bool	handle_env(t_astnode *head, t_data *data);
bool	handle_unset(t_astnode *head, t_data *data);
bool	handle_exit(t_astnode *head, t_data *data);
bool	handle_export(t_astnode *head, t_data *data);
bool	handle_exec(t_astnode *head, t_data *data);
bool	handle_pipe(t_astnode *head, t_data *data);
// Built in functions for execution

#endif
