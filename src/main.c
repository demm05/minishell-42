# include "../inc/parser.h"
# include "../inc/exec.h"

int	free_data(t_data *data)
{
	if (data->l)
		free_lexer(data->l);
	if (data->head)
		free_ast(&data->head);
	free(data->line);
	return (0);
}

t_data	*init(int argc, char **argv, char **envp)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->env = init_env(envp);
	data->exit_status = 0;
	return (data);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	data = init(argc, argv, envp);
	while (1)
	{
		data->line = readline("Prompt > ");
		if (!data->line)
			break ;
		data->l = new_lexer(data->line);
		generate_tokens(data->l);
		data->head = parse(data->l);
		if (data->head)
		{
			print_ast(data->head, 0);
			printf("\nResult: \n");
			exec(data);
		}
		free_data(data);
	}
	if (data->env)
		free_env(&data->env);
	return (0);
}
