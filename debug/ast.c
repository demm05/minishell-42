#include "../src/ast/ast_private.h"
#include "../src/eval/eval_private.h"
#include "../src/lexer/lexer_private.h"
#include "../src/extra/extra_private.h"
#include <stdlib.h>

t_astnode	*head;

int	main(int argc, char **argv, char **envp)
{
	t_token	tok;
	t_data	data;

	data.env = init_env(argv, envp);
	tok.type = EXEC; 
	tok.literal = NULL;
	head = new_astnode(&tok);
	tok.type = SSPACE;
	add_child(head, new_astnode(&tok));
	tok.type = SSPACE;
	add_child(head, new_astnode(&tok));
	tok.literal = t_strdup("HELLO _WORLD");
	tok.type = WORD;
	add_child(head, new_astnode(&tok));
	tok.type = SSPACE;
	add_child(head, new_astnode(&tok));
	expand_tree(head, &data);
	print_ast(head, 0);
	free_env(&data.env);
	free_ast(&head);
}
