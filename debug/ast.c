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
	tok.literal = NULL;
	tok.type = ECHO; 
	head = new_astnode(&tok);
	tok.type = DQUOTE;
	add_child(head, new_astnode(&tok));
	tok.type = WORD;
	tok.literal = ft_strdup("HELLO  ");
	add_child(head, new_astnode(&tok));
	tok.type = EXPAND_VAR;
	tok.literal = ft_strdup("SHLVL");
	add_child(head, new_astnode(&tok));
	tok.type = EXPAND_VAR;
	tok.literal = ft_strdup("PWD");
	add_child(head, new_astnode(&tok));
	tok.type = WORD;
	tok.literal = ft_strdup("  WORLD");
	add_child(head, new_astnode(&tok));
	tok.type = DQUOTE;
	add_child(head, new_astnode(&tok));
	my_expand_tree(&data, head);
	print_ast(head, 0);
	free_env(&data.env);
	free_ast(&head);
}
