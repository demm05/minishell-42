/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelnyk <dmelnyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:40:06 by dmelnyk           #+#    #+#             */
/*   Updated: 2025/03/18 11:02:44 by dmelnyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./eval_private.h"

static int	is_numeric(const char *str)
{
	int	i;

	i = 0;
	if (!str || !str[i])
		return (0);
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (str[i] == '\0')
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	get_status(t_astnode *head, t_data *data)
{
	char	*arg;

	if (head && head->literal)
	{
		arg = head->literal;
		if (!is_numeric(arg))
		{
			ft_fprintf(STDERR_FILENO, "exit: %s: numeric "
				"argument required\n", arg);
			return (2);
		}
		else
		{
			if (head->next)
			{
				ft_fprintf(STDERR_FILENO, "exit: too many arguments\n");
				return (-1);
			}
			else
				return ((int)ft_atol(arg) % 256);
		}
	}
	return (data->exit_status);
}

bool	handle_exit(t_astnode *head, t_data *data)
{
	int		status;

	status = get_status(head->children, data);
	if (status == -1)
	{
		data->exit_status = 1;
		return (1);
	}
	free_everything(data);
	exit(status);
}
