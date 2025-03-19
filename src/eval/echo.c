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

bool	handle_echo(t_astnode *head, t_data *data)
{
	bool		newline;
	bool		first_arg;
	t_astnode	*h;

	if (!head)
		return (1);
	newline = true;
	if (head->children)
	{
		if (ft_strncmp(head->children->literal, "-n", 2) == 0)
		{
			newline = false;
			h = head->children->next;
		}
		else
			h = head->children;
		first_arg = true;
		while (h)
		{
			if (!first_arg)
				write(STDOUT_FILENO, " ", 1);
			first_arg = false;
			write(STDOUT_FILENO, h->literal, ft_strlen(h->literal));
			h = h->next;
		}
	}
	if (newline)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}
