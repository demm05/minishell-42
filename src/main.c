# include "../inc/parser.h"

int	main(int argc, char **argv)
{
	t_lexer	*l;
	char	*line;
	t_astnode	*head;

	while (1)
	{
		line = readline("Promt > ");
		if (!line)
			break ;
		l = new_lexer(line);
		generate_tokens(l);
		head = parse(l);
		if (head)
		{
			print_tokens(l->tokens);
			print_ast(head, 0);
			printf("\n");
			free_ast(&head);
			free_lexer(l);
		}
		free(line);
	}
	return (0);
}
