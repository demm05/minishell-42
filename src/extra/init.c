/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelnyk <dmelnyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:52:53 by dmelnyk           #+#    #+#             */
/*   Updated: 2025/03/18 11:03:44 by dmelnyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./extra_private.h"
#include "../tokenization/lexer.h"
#include "../ast/ast.h"
#include "libft.h"
#include <stdlib.h>

int	free_data(t_data *data)
{
	free(data->line);
	data->line = NULL;
	return (0);
}

t_data	*init(int argc, char **argv, char **envp)
{
	t_data	*data;

	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		return (NULL);
	data->env = init_env(argv, envp);
	data->prompt = "Prompt > ";
	data->l = ft_calloc(1, sizeof(t_lexer));
	return (data);
}
