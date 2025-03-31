#include "expansion_private.h"
#include <stdlib.h>

static inline void	set_type(t_astnode *head)
{
	char			*s;

	s = head->literal;
	if (ft_strcmp(s, "echo") == 0)
		head->type = ECHO;
	else if (ft_strcmp(s, "pwd") == 0)
		head->type = PWD;
	else if (ft_strcmp(s, "cd") == 0)
		head->type = CD;
	else if (ft_strcmp(s, "export") == 0)
		head->type = EXPORT;
	else if (ft_strcmp(s, "env") == 0)
		head->type = ENV;
	else if (ft_strcmp(s, "unset") == 0)
		head->type = UNSET;
	else if (ft_strcmp(s, "exit") == 0)
		head->type = EXIT;
}

void	do_exec(t_astnode *head, t_data *data)
{
	t_astnode	*new;
	t_astnode	*old_last;
	char		**s;

	s = expand_word(head, data);
	if (!s)
		return ;
	free(head->literal);
	head->literal = *s;
	set_type(head);	
	new = create_nodes(s + 1);
	free(s);
	if (!new)
		return ;
	if (!head->children)
	{
		head->children = new;
		return ;
	}
	new->prev->next = head->children;
	old_last = head->children->prev;
	head->children = new;
	head->children->prev = old_last;
}
