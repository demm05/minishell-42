/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelnyk <dmelnyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:40:12 by dmelnyk           #+#    #+#             */
/*   Updated: 2025/03/11 17:06:06 by dmelnyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/parser.h"
# include "../inc/exec.h"
#include <readline/readline.h>

int	free_data(t_data *data)
{
	if (data->l)
	{
		if (data->l->tokens && data->l->tokens->type == EOL)
			free(data->l->tokens);
		free_lexer(data->l);
		data->l = NULL;
	}
	if (data->head)
		free_ast(&data->head);
	free(data->line);
	data->line = NULL;
	return (0);
}

t_data	*init(int argc, char **argv, char **envp)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	ft_bzero(data, sizeof(t_data));
	data->env = init_env(argv, envp);
	data->prompt = "Prompt > ";
	return (data);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;
	int		status;

	data = init(argc, argv, envp);
	while (1)
	{
		mini_read(data);
		if (!data->line)
			break ;
		data->l = new_lexer(data->line);
		generate_tokens(data->l);
		data->head = parse(data->l);
		printf("line: %s\n", data->line);
		print_tokens(data->l->tokens);
		if (data->head && data->l->tokens && data->l->tokens->type != EOL)
		{
			print_ast(data->head, 0);
			printf("\nResult: \n");
			exec(data);
		}
		free_data(data);
	}
	if (data->env)
		free_env(&data->env);
	free_data(data);
	status = data->exit_status;
	rl_clear_history();
	free(data);
	return (status);
}
