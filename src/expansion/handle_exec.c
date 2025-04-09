/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelnyk <dmelnyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 16:41:10 by dmelnyk           #+#    #+#             */
/*   Updated: 2025/04/09 16:41:10 by dmelnyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion_private.h"

void	do_exec(t_astnode *head, t_data *data);

static void	process_exec_children(t_astnode *head, t_data *data)
{
	t_astnode	*cur;
	t_astnode	*next;

	cur = head->children;
	while (cur)
	{
		next = cur->next;
		if (cur->type == WORD)
			do_child(head->children, cur, data);
		cur = next;
	}
}

static void	cleanup_exec_children(t_astnode *head)
{
	while (head->children)
	{
		if (head->children->literal && *head->children->literal)
		{
			free(head->literal);
			head->literal = head->children->literal;
			head->children->literal = NULL;
			ast_delete_first_child(head);
			break ;
		}
		ast_delete_first_child(head);
	}
}

void	_handle_exec(t_astnode *head, t_data *data)
{
	do_exec(head, data);
	process_exec_children(head, data);
	if (head->children && (!head->literal || !*head->literal))
		cleanup_exec_children(head);
	head->childs = ast_get_size(head->children);
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
