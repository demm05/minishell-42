/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelnyk <dmelnyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:44:16 by dmelnyk           #+#    #+#             */
/*   Updated: 2025/03/12 12:38:43 by dmelnyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./eval_private.h"
#include <stdbool.h>

static t_astnode	*skip_n_flags(t_astnode *cur, bool *newline)
{
	int	i;

	while (cur && cur->literal[0] == '-' && cur->literal[1] == 'n')
	{
		i = 1;
		while (cur->literal[i] == 'n')
			i++;
		if (cur->literal[i] == '\0')
		{
			*newline = false;
			cur = cur->next;
		}
		else
			break ;
	}
	return (cur);
}

bool	handle_echo(t_astnode *head, t_data *data)
{
	bool		newline;
	bool		first_arg;
	t_astnode	*cur;

	(void)data;
	if (!head)
		return (1);
	newline = true;
	cur = skip_n_flags(head->children, &newline);
	first_arg = true;
	while (cur)
	{
		if (!first_arg)
			write(STDOUT_FILENO, " ", 1);
		first_arg = false;
		write(STDOUT_FILENO, cur->literal, ft_strlen(cur->literal));
		cur = cur->next;
	}
	if (newline)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}
