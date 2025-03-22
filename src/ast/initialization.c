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
#include "../construct_word/const_word.h"
#include <stdlib.h>
#include <stdio.h>

t_astnode	*new_astnode(t_token *tok)
{
	t_astnode	*node;

	node = ft_calloc(1, sizeof(t_astnode));
	node->type = tok->type;
	node->literal = tok->literal;
	return (node);
}

void	add_child(t_astnode *parent, t_astnode *child)
{
	if (!parent || !child)
		return ;
	parent->childs++;
	if (!parent->children)
	{
		parent->children = child;
		parent->children->prev = child;
		return ;
	}
	child->prev = parent->children->prev;
	parent->children->prev->next = child;
	parent->children->prev = child;
}

void	print_ast(t_astnode *node, int depth)
{
	int			i;
	t_astnode	*cur;

	if (depth == 0)
		printf("Abstract syntax tree: \n");
	i = 0;
	while (i++ < depth)
		printf("  ");
	printf("%s", decode(node->type));
	printf(" (%s)\n", node->literal);
	cur = node->children;
	while (cur)
	{
		print_ast(cur, depth + 1);
		cur = cur->next;
	}
}

void	free_ast(t_astnode **node)
{
	t_astnode	*next;

	if (!node || !*node)
		return ;
	while ((*node)->children)
	{
		next = (*node)->children->next;
		free_ast(&(*node)->children);
		(*node)->children = next;
	}
	free((*node)->literal);
	free(*node);
	*node = NULL;
}
