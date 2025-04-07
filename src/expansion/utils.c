/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelnyk <dmelnyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 18:24:16 by dmelnyk           #+#    #+#             */
/*   Updated: 2025/04/07 18:24:16 by dmelnyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion_private.h"

t_token_type	get_exec_type(char *s)
{
	if (ft_strcmp(s, "echo") == 0)
		return (ECHO);
	else if (ft_strcmp(s, "pwd") == 0)
		return (PWD);
	else if (ft_strcmp(s, "cd") == 0)
		return (CD);
	else if (ft_strcmp(s, "export") == 0)
		return (EXPORT);
	else if (ft_strcmp(s, "env") == 0)
		return (ENV);
	else if (ft_strcmp(s, "unset") == 0)
		return (UNSET);
	else if (ft_strcmp(s, "exit") == 0)
		return (EXIT);
	return (EXEC);
}

t_astnode	*create_nodes(char **ss)
{
	t_astnode	*res;
	t_token		t;
	int			i;

	if (!ss || !*ss)
		return (NULL);
	i = 0;
	t.type = WORD;
	res = NULL;
	while (ss[i])
	{
		t.literal = ss[i];
		t.size = ft_strlen(ss[i]);
		append_astnode(&res, new_astnode(&t));
		i++;
	}
	return (res);
}
