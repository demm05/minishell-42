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


//static bool	is_valid_identifier(char *arg)
//{
//	while (*arg)
//	{
//		if (*arg++ == '=')
//			return (false);
//		if ()
//	}
//}

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

bool	is_valid_identifier(char *s)
{
	if (!s || !*s)
		return (false);
	if (!((*s >= 'A' && *s <= 'Z') || (*s >= 'a' && *s <= 'z') || *s == '_'))
		return (false);
	s++;
	while (*s && *s != '=')
	{
		if (!((*s >= 'A' && *s <= 'Z') || (*s >= 'a' && *s <= 'z')
			|| (*s >='0' && *s <= '9') || *s == '_'))
			return (false);
		s++;
	}
	return (true);
}

bool	handle_export(t_astnode *head, t_data *data)
{
	//TODO:
	//use `add_env` function to add
	// Value can start from _ or any alphabetical char and followed by _ or number or alphabet
	// Inputting `export HELLO` doesn't set but `export HELLO=` sets empty string.
	t_astnode	*cur;
	char		*arg;
	char		*equal_sign;
	char		*key;
	char		*value;

	cur = head->children;
	if (!cur)
	{
		print_allenv(data);
		return (0);
	}
	while (cur)
	{
		arg = cur->literal;
		equal_sign = ft_strchr(arg, '=');
		if (equal_sign)
		{
			*equal_sign = '\0';
			key = arg;
			value = equal_sign + 1;
			if (!is_valid_identifier(key))
			{
				printf("export: `%s': not a valid identifier\n", arg);
				*equal_sign = '=';
				cur = cur->next;
				continue ;
			}
			//TODO:delete
			printf("Key: %s, Value: %s\n", key, value);
			if (!add_env(&(data->env), key, value))
				printf("export: failed to add/update variable: %s\n", key);
			*equal_sign = '=';
		}
		else
		{
			if (!is_valid_identifier(arg))
				printf("export: `%s': not a valid identifier\n", arg);
		}
		cur = cur->next;
	}
	return (0);
}
