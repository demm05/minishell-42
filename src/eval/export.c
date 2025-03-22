/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelnyk <dmelnyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:40:21 by dmelnyk           #+#    #+#             */
/*   Updated: 2025/03/12 12:47:36 by dmelnyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./eval_private.h"
#include <stdio.h>

static void	print_allenv(t_data *data)
{
	t_env	*cur;

	cur = data->env;
	while (cur)
	{
		if (cur->value)
			printf("declare -x %s=\"%s\"\n", cur->key, cur->value);
		else
			printf("declare -x %s\n", cur->key);
		cur = cur->next;
	}
}

static bool	is_valid_identifier(char *s)
{
	if (!s || !*s)
		return (false);
	if (!((*s >= 'A' && *s <= 'Z') || (*s >= 'a' && *s <= 'z') || *s == '_'))
		return (false);
	s++;
	while (*s && *s != '=')
	{
		if (!((*s >= 'A' && *s <= 'Z') || (*s >= 'a' && *s <= 'z')
				|| (*s >= '0' && *s <= '9') || *s == '_'))
			return (false);
		s++;
	}
	return (true);
}

static bool	process_export_arg(char *arg, t_data *data)
{
	char		*equal_sign;
	char		*key;
	char		*value;

	equal_sign = ft_strchr(arg, '=');
	if (equal_sign)
	{
		*equal_sign = '\0';
		key = arg;
		value = equal_sign + 1;
		if (!is_valid_identifier(key))
		{
			fprintf(stderr, "export: `%s': not a valid identifier\n", arg);
			*equal_sign = '=';
			return (true);
		}
		if (!add_env(&(data->env), ft_strdup(key), ft_strdup(value)))
			fprintf(stderr, "export: failed to add/update variable: %s\n", key);
		*equal_sign = '=';
	}
	else if (!is_valid_identifier(arg))
	{
		fprintf(stderr, "export: `%s': not a valid identifier\n", arg);
		return (true);
	}
	return (false);
}

bool	handle_export(t_astnode *head, t_data *data)
{
	t_astnode	*cur;
	bool		result;

	cur = head->children;
	if (!cur)
	{
		print_allenv(data);
		return (0);
	}
	result = 0;
	while (cur)
	{
		if (process_export_arg(cur->literal, data))
			result = 1;
		cur = cur->next;
	}
	if (result)
		data->exit_status = 1;
	return (result);
}
