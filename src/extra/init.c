/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelnyk <dmelnyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:52:53 by dmelnyk           #+#    #+#             */
/*   Updated: 2025/03/12 15:47:51 by dmelnyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./extra_private.h"
#include "../lexer/lexer.h"
#include "../ast/ast.h"
#include "libft.h"
#include <stdlib.h>

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
