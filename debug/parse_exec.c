#include "parser.h"


/*int	main(void)
{
	t_lexer	*l = NULL;
	t_astnode	*node = NULL;

	l = new_lexer("cat Makefile >a >b >c");	
	generate_tokens(l);
	node = parse_exec(l->tokens);
	printf("%s\n", l->input);
	if (node != NULL)
		print_ast(node, 0);
	else
		printf("Error got null\n");
	free_lexer(l);
}*/
