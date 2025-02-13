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
		while (1 && !exit_s)
		{
			t = get_next_token(l);
			if (t->type == EOL)
				break ;
			if (t->type == EXIT)
				exit_s = 1;
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
