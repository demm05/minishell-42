# include "../inc/minishell.h"
# include "../inc/parser.h"

int	main(int argc, char **argv)
{
	t_lexer	*l;
	t_token	*t;
	char	*line;

	while (1)
	{
		line = readline("Promt > ");
		l = new_lexer(line);
		while (1)
		{
			t = get_next_token(l);
			printf("Type: %d Literal: %s\n", t->type, t->literal);
			if (t->type == EOL)
				break ;
			free(t);
		}
		free(line);
		free(l);
	}
	return (0);
}
