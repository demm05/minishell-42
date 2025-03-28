#include "expansion_private.h"
#include "minishell.h"

void	expand_head(t_astnode *head, t_data *data)
{
	t_astnode	*cur;
	t_astnode	*next;

	if (!head || !data)
		return ;
	else if (head->type == PIPE)
	{
		expand_head(head->children, data);
		return ;
	}
	else if (head->type != EXEC)
		return ;
	do_head(head, data);
	cur = head->children;
	while (cur)
	{
		next = cur->next;
		if (cur->type == PIPE || cur->type == EXEC)
			expand_head(cur, data);
		else if (cur->type == WORD || cur->type == PATH)
			do_child(head->children, cur, data);
		cur = next;
	}
}
