#include "expansion_private.h"
#include <stdlib.h>

void	do_child(t_astnode *head, t_astnode *cur, t_data *data)
{
	t_astnode	*new;
	t_astnode	*next;
	t_astnode	*new_last;
	char		**s;

	s = expand_word(cur, data);
	if (!s)
		return ;
	free(cur->literal);
	cur->literal = *s;
	new = create_nodes(s + 1);
	free(s);
	if (!new)
		return ;
	next = cur->next;
	new_last = new->prev;
	if (!head->next)
		head->prev = new_last;
	else if (next)
		next->prev = new_last;
	new_last->next = next;	
	cur->next = new;
	new->prev = cur;
}
