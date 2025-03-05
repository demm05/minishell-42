#include "../../inc/exec.h"

static int	get_fd(t_astnode *head);

bool	handle_redir(t_astnode *head, t_data *data)
{
	if (!head || !data)
		return (0);
	get_fd(head->children);
	return (0);
}

static int	get_fd(t_astnode *head)
{
	while (head)
	{
		if (head->type == PATH)
			break ;
		head = head->next;
	}
	if (!head)
		return (-1);
	puts("Opening file");
	return (0);
}
