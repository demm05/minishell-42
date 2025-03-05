#include "../../inc/exec.h"
#include "../../inc/parser.h"

bool	handle_exit(t_astnode *head, t_data *data)
{
	int	status;

	status = data->exit_status;
	if (data->l)
		free_lexer(data->l);
	if (data->head)
		free_ast(&data->head);
	if (data->env)
		free_env(&data->env);
	free(data->line);
	exit (status);
}
