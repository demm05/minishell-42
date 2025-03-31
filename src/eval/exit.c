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
#include "../heredoc/heredoc.h"
#include <stdlib.h>

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

static long	ft_strtol(const char *str, char **endptr)
{
	long		result;
	int			sign;

	result = 0;
	sign = 1;
	while (*str && ft_isspace(*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str && ft_isdigit((unsigned char)*str))
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	if (endptr)
		*endptr = (char *)str;
	return (sign * result);
}

static int	get_status(t_astnode *head, t_data *data)
{
	int		status;
	char	*arg;

	status = data->exit_status;
	if (head->children && head->children->literal)
	{
		arg = head->children->literal;
		if (!is_numeric(arg))
		{
			fprintf(stderr, "exit: %s: numeric argument required\n", arg);
			status = 2;
		}
		else
		{
			if (head->children->next)
			{
				fprintf(stderr, "exit: too many arguments\n");
				status = 1;
			}
			else
				status = (int)ft_strtol(arg, NULL) % 256;
		}
	}
	return (status);
}

bool	handle_exit(t_astnode *head, t_data *data)
{
	int		status;

	status = get_status(head, data);
	if (data->head)
		free_ast(&data->head);
	if (data->env)
		free_env(&data->env);
	if (data->tmp)
	{
		tmp_del(data->tmp);
		free(data->tmp->files);
		free(data->tmp->tmpdir);
		free(data->tmp);
	}
	free(data->line);
	exit(status);
}
