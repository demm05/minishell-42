#include "expansion_private.h"
#include "minishell.h"

void	expand_head(t_astnode *head, t_data *data)
{
	t_astnode	*cur;
	t_astnode	*next;

	if (!head || !data)
		return ;
	if (is_redir(head->type) || head->type == PIPE)
	{
		expand_head(head->children, data);
		expand_head(head->children->next, data);
		return ;
	}
	else if (head->type == EXEC)
		do_exec(head, data);
	else if (head->type == PATH)
	{
		do_path(head, data);
		return ;
	}
	else
		return ;
	cur = head->children;
	while (cur)
	{
		next = cur->next;
		if (cur->type == WORD || cur->type == PATH)
			do_child(head->children, cur, data);
		cur = next;
	}
}
