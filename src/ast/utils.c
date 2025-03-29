/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelnyk <dmelnyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 11:26:53 by dmelnyk           #+#    #+#             */
/*   Updated: 2025/03/22 13:24:59 by dmelnyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ast_private.h"
#include <stdio.h>

t_astnode	*new_astnode(t_token *tok)
{
	t_astnode	*node;

	node = ft_calloc(1, sizeof(t_astnode));
	node->type = tok->type;
	node->literal = tok->literal;
	return (node);
}

t_astnode	*append_astnode(t_astnode **head, t_astnode *new)
{
	if (!*head)
	{
		new->prev = new;
		*head = new;
	}
	else
	{
		new->prev = (*head)->prev;
		(*head)->prev->next = new;
		(*head)->prev = new;
	}
	return (new);
}

void	add_child(t_astnode *parent, t_astnode *child)
{
	if (!parent || !child)
		return ;
	parent->childs++;
	append_astnode(&parent->children, child);
}

void	print_ast(t_astnode *node, int depth)
{
	int			i;
	t_astnode	*cur;

	i = 0;
	while (i++ < depth)
		printf("  ");
	printf("%s", decode(node->type));
	printf(" (%s)\n", node->literal);
	if (node->children)
		print_ast(node->children, depth + 1);
	cur = node->next;
	while (cur)
	{
		print_ast(cur, depth);
		cur = cur->next;
	}
}

void	free_ast(t_astnode **node)
{
	t_astnode	*next;
	t_astnode	*cur;

	if (!node || !*node)
		return ;
	if ((*node)->children)
		free_ast(&(*node)->children);
	cur = (*node)->next;
	while (cur)
	{
		next = cur->next;
		if (cur->children)
			free_ast(&cur->children);
		free(cur->literal);
		free(cur);
		cur = next;
	}
	free((*node)->literal);
	free(*node);
	*node = NULL;
}
