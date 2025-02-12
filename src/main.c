# include "../inc/minishell.h"
# include "../inc/parser.h"

int	main(int argc, char **argv)
{
	t_lexer	*l;
	t_token	*t;
	char	*line;
	int		i;

	while (1)
	{
		line = readline("Promt > ");
		l = new_lexer(line);
		while (1)
		{
			t = get_next_token(l);
			if (t->type == EOL)
				break ;
			printf("Type: %d Literal: ", t->type);
			i = 0;
			while (i < t->size)
				printf("%c", t->literal[i++]);
			printf("\n");
			free(t);
		}
		free(line);
		free(l);
	}
	return (0);
}
