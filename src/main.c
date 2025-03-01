# include "../inc/parser.h"

void	print_tokens(t_token *token)
{
	printf("Stream of tokens: ");
	while (token->next)
	{
		printf("%s -> ", decode(token->type));
		token = token->next;
	}
	printf("%s", decode(token->type));
	printf("\n\n");
}

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
		print_tokens(l->tokens);
		if (head)
		{
			print_ast(head, 0);
			printf("\n");
			free_ast(&head);
			free_lexer(l);
		}
		free(line);
	}
	return (0);
}
