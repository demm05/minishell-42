#include "../../inc/parser.h"

t_astnode	*new_astnode(t_token *tok)
{
	t_astnode	*node;

	node = malloc(sizeof(t_astnode));
	node->type = tok->type;
	node->lit_size = tok->size;
	node->literal = tok->literal;
	node->children = NULL;
	node->childs = 0;
	return (node);
}

void add_child(t_astnode *parent, t_astnode *child)
{
	t_astnode	**old_children;

	if (!parent || !child)
		return ;
	old_children = parent->children;
	parent->childs++;
	parent->children = malloc(sizeof(t_astnode *) * parent->childs);
	if (!parent->children)
		return ;
	ft_memcpy(parent->children, old_children, sizeof(t_astnode *) * (parent->childs - 1));
	parent->children[parent->childs - 1] = child;
	free(old_children);
}

void	print_ast(t_astnode *node, int depth)
{
	int	i;

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

	i = 0;
	while (i < node->childs)
		print_ast(node->children[i++], depth + 1);
}

void	free_ast(t_astnode **node)
{
	int	i;

	if (!node || !*node)
		return ;
	i = 0;
	while (i < (*node)->childs)
		free_ast(&(*node)->children[i++]);
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
