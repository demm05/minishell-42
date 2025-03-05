#ifndef EINTERNAL_H
# define EINTERNAL_H

# include "./types.h"

void   exec(t_data *data);

// Built in functions for execution
bool   handle_echo(t_astnode *head, t_data *data);
bool   handle_cd(t_astnode *head, t_data *data);
bool   handle_pwd(t_astnode *head, t_data *data);
bool   handle_env(t_astnode *head, t_data *data);
bool   handle_unset(t_astnode *head, t_data *data);
bool   handle_exit(t_astnode *head, t_data *data);
bool   handle_export(t_astnode *head, t_data *data);
bool   handle_exec(t_astnode *head, t_data *data);
bool   handle_pipe(t_astnode *head, t_data *data);
bool   handle_redir(t_astnode *head, t_data *data);
// Built in functions for execution
//
// ENV
t_env	*init_env(char **envp);
void	free_env(t_env **head);
t_env	*append_env(t_env **head, char *key, char *value);
t_env	*getenv_val(t_env *head, char *key);
// ENV
char	*get_curent_dir(void);

#endif
