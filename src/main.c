# include "../inc/parser.h"

int	main(int argc, char **argv)
{
	t_lexer	*l;
	t_token	*t;
	char	*line;
	int		i;
	int		exit_s = 0;

	while (!exit_s)
	{
		line = readline("Promt > ");
		if (!line)
			break ;
		l = new_lexer(line);
		generate_tokens(l);
		t = l->tokens;
		while (t)
		{
			printf("Type: %d Literal: ", t->type);
			i = 0;
			while (i < t->size)
				printf("%c", t->literal[i++]);
			printf("\n");
			t = t->next;
		}
		free(line);
		free_lexer(l);
	}
	return (0);
}
