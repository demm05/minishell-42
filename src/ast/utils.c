#include "./ast_private.h"
#include <stdlib.h>
#include <stdio.h>

t_astnode	*new_astnode(t_token *tok)
{
	t_astnode	*node;

	node = malloc(sizeof(t_astnode));
	node->type = tok->type;
	node->literal = tok->literal;
	node->children = NULL;
	node->next = NULL;
	node->prev = NULL;
	node->childs = 0;
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

/**
 * @brief Removes a node from a doubly linked list of AST nodes.
 *
 * This function removes a specified node (`*node`) from a doubly linked
 * list of `t_astnode` structures. It handles cases where the node to be
 * removed is the head of the list, a node in the middle, or the last node.
 * The function correctly updates the `prev` and `next` pointers of
 * surrounding nodes, and it frees the memory occupied by the removed node.
 * It considers the edge cases, like empty list. The function uses double
 * pointer because node could be head of the my slight modified doubly
 * linked list, and in the head node the last node of the linked list is
 * kept, so there is no need to iterate through the whole list.
 *
 * @param head A double pointer to the head of the AST node list.
 *             This is a double pointer because the head of the list might
 *             be the node being removed, requiring modification of the head.
 * @param node A double pointer to the node to be removed. It is double
 *             pointer because after freeing node should be equal to NULL.
 */
void	ast_pop(t_astnode **head, t_astnode **node)
{
	t_astnode	*prev;
	t_astnode	*next;

	if (!node || !*node || !head || !*head)
		return ;
	prev = (*node)->prev;
	next = (*node)->next;
	free(*node);
	*node = NULL;
	if (!*head)
		return ;
	prev->next = next;
	if (!(*head)->next)
		(*head)->prev = *head;
	else
		(*head)->prev = prev;
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

bool	match(t_token *token, t_token_type expected[], int size)
{
	if (!token)
		return (0);
	while (size-- > 0)
	{
		if (*expected == token->type)
			return (1);
		expected++;
	}
	return (0);
}
