#ifndef EXEC_H
# define EXEC_H

# include "./minishell.h"

typedef bool (*builtin_func_ptr)(t_astnode *head, t_data *data);

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
