# include "../inc/parser.h"

int	free_data(t_data *data)
{
	if (data->l)
		free_lexer(data->l);
	if (data->head)
		free_ast(&data->head);
	return (0);
}

int	main(int argc, char **argv)
{
	char	*line;
	t_data	data;

	while (1)
	{
		line = readline("Promt > ");
		if (!line)
			break ;
		data.l = new_lexer(line);
		generate_tokens(data.l);
		data.head = parse(data.l);
		if (data.head)
		{
			print_ast(data.head, 0);
			printf("\nResult: \n");
			exec(&data);
		}
		free_data(&data);
		free(line);
	}
	return (0);
}
