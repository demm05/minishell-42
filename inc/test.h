/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelnyk <dmelnyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:24:40 by dmelnyk           #+#    #+#             */
/*   Updated: 2025/03/14 14:07:33 by dmelnyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
# define TEST_H

#include "criterion/include/criterion/criterion.h"
#include "criterion/include/criterion/redirect.h"
#include "../src/ast/ast_private.h"
#include "../src/eval/eval_private.h"
#include "../src/tokenization/lexer_private.h"
#include "../src/extra/extra_private.h"
#include <stdlib.h>

char	**envp;

void	create_env(int size, ...)
{
	char	*s;
	va_list	args;
	int		i;

	va_start(args, size);
	envp = malloc(sizeof(char *) * (size + 1));
	i = 0;
	while (i < size)
	{
		s = va_arg(args, char *);
		envp[i++] = ft_strdup(s);
	}
	va_end(args);
	envp[i] = NULL;
}

void	free_envp(void)
{
	int	i;

	if (!envp)
		return ;
	i = 0;
	while (envp[i])
		free(envp[i++]);
	free(envp);
	envp = NULL;
}

#endif
