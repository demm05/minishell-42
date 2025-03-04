#include "../../inc/exec.h"

bool			eval(t_astnode *head, t_data *data);
builtin_func_ptr is_built_in(t_token_type type);

void	exec(t_data *data)
{
	if (!data->head)
		return ;
	eval(data->head, data);
}

bool	eval(t_astnode *head, t_data *data)
{
	if (head->type == AND)
	{
		if (eval(head->children, data))
			return (1);
		if (eval(head->children->next, data))
			return (1);
	}
	if (head->type == OR)
	{
		if (!eval(head->children, data))
			return (0);
		if (!eval(head->children->next, data))
			return (0);
		return (1);
	}
	if (head->type == EXEC)
		return (handle_exec(head, data));
	if (is_built_in(head->type))
		return(is_built_in(head->type)(head, data));
	if (head->type == PIPE)
		return (handle_pipe(head, data));
	return (1);
}

builtin_func_ptr is_built_in(t_token_type type)
{
	if (type == ECHO)
		return (handle_echo);
	if (type == CD)
		return (handle_cd);
	if (type == PWD)
		return (handle_pwd);
	if (type == EXPORT)
		return (handle_exit);
	if (type == UNSET)
		return (handle_unset);
	if (type == EXIT)
		return (handle_exit);
	if (type == ENV)
		return (handle_env);
	return (NULL);
}
