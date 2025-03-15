/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelnyk <dmelnyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:40:12 by dmelnyk           #+#    #+#             */
/*   Updated: 2025/03/14 15:11:34 by dmelnyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <unistd.h>
#include "../inc/minishell.h"
#include "extra/extra.h"
#include "lexer/lexer.h"
#include "ast/ast.h"
#include "libft.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;
	int		status;

	data = init(argc, argv, envp);
	while (1)
	{
		if (isatty(fileno(stdin)))
			mini_read(data);
		else
			data->line = get_next_line(fileno(stdin));
		if (!data->line)
			break ;
		data->l = new_lexer(data->line);
		generate_tokens(data->l);
		data->head = parse(data->l);
		if (data->head && data->l->tokens && data->l->tokens->type != EOL)
		{
			//print_tokens(data->l->tokens);
			print_ast(data->head, 0);
			//printf("\nResult: \n");
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
	//fprintf(stderr, "exit\n");
	return (status);
}
