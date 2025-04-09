/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_headnode.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelnyk <dmelnyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 18:23:48 by dmelnyk           #+#    #+#             */
/*   Updated: 2025/04/07 18:23:49 by dmelnyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion_private.h"

void		do_path(t_astnode *head, t_data *data);
void		do_exec(t_astnode *head, t_data *data);
void		do_child(t_astnode *head, t_astnode *cur, t_data *data);

void	expand_head(t_astnode *head, t_data *data)
{
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
		_handle_exec(head, data);
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
		ft_fprintf(STDERR_FILENO, "%s: ambiguous redirect\n", head->literal);
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
