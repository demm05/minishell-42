#include "../../inc/parser.h"

t_astnode	*new_astnode(t_token *tok)
{
	t_astnode	*node;

	node = malloc(sizeof(t_astnode));
	node->type = tok->type;
	node->lit_size = tok->size;
	node->literal = tok->literal;
	node->children = NULL;
	node->next = NULL;
	node->prev = NULL;
	node->childs = 0;
	return (node);
}

void add_child(t_astnode *parent, t_astnode *child)
{
	if (!parent || !child)
		return ;
	if (!parent->children)
	{
		parent->children = child;
		parent->prev = child;
		return ;
	}
	parent->prev->next = child;
	parent->prev = child;
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
	printf(" (");
	i = 0;
	while (i < node->lit_size)
		printf("%c", node->literal[i++]);
	printf(")");
	printf("\n");

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
		next = (*node)->children->next;;
		free_ast(&(*node)->children);
		(*node)->children = next;
	}
	free(*node);
	*node = NULL;
}

bool	match(t_token *token, t_token_type expected[], int size)
{
	while (size-- > 0)
	{
		if (*expected == token->type)
			return (1);
		expected++;
	}
	return (0);
}
