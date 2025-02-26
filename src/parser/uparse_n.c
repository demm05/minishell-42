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

void		add_child(t_astnode *parent, t_astnode *child)
{
	parent->childs++;
	parent->children = realloc(parent->children, parent->childs* sizeof(t_astnode *));
	parent->children[parent->childs- 1] = child;
}

void	print_ast(t_astnode *node, int depth)
{
	int	i;

	// Print indentation
	for (i = 0; i < depth; i++)
		printf("  ");

	// Print node type and literal
	printf("%s", decode(node->type));
	printf(" (");
	for (i = 0; i < node->lit_size; i++)
		printf("%c", node->literal[i]);
	printf(")");
	printf("\n");

	// Print children
	for (i = 0; i < node->childs; i++)
		print_ast(node->children[i], depth + 1);
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
