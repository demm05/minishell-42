#include "expansion_private.h"

void	do_path(t_astnode *head, t_data *data);
void	do_exec(t_astnode *head, t_data *data);
void	do_child(t_astnode *head, t_astnode *cur, t_data *data);

void	expand_head(t_astnode *head, t_data *data)
{
	t_astnode	*cur;
	t_astnode	*next;

	if (!head || !data)
		return ;
	if (is_redir(head->type))
		do_path(head->children, data);
	if (head->type == PIPE)
	{
		expand_head(head->children, data);
		expand_head(head->children->next, data);
	}
	else if (head->type == EXEC)
	{
		cur = head->children;
		do_exec(head, data);
		while (cur)
		{
			next = cur->next;
			if (cur->type == WORD || cur->type == PATH)
				do_child(head->children, cur, data);
			cur = next;
		}
		head->childs = ast_get_size(head->children);
	}
}

void	do_exec(t_astnode *head, t_data *data)
{
	t_astnode	*new;
	t_astnode	*old_last;
	char		**s;

	s = expand_word(head, data, 1);
	if (!s)
		return ;
	free(head->literal);
	head->literal = *s;
	head->type = get_exec_type(head->literal);
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

void	do_child(t_astnode *head, t_astnode *cur, t_data *data)
{
	t_astnode	*new;
	t_astnode	*next;
	t_astnode	*new_last;
	char		**s;

	s = expand_word(cur, data, 1);
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

void	do_path(t_astnode *head, t_data *data)
{
	char		**s;
	int			i;

	s = expand_word(head, data, 0);
	if (!s)
		return ;
	if (s[1])
	{
		fprintf(stderr, "%s: ambiguous redirect\n", head->literal);
		i = 0;
		while (s[i])
			free(s[i++]);
		free(s);
		return ;
	}
	free(head->literal);
	head->literal = *s;
	free(s);
}
