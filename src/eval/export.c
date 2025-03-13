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
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

bool	handle_export(t_astnode *head, t_data *data)
{
	t_astnode	*cur;
	char		**s;

	if (!head || !data || !head->children || head->type != EXPORT)
		return (1);
	cur = head->children;
	while (cur)
	{
		if (cur->literal && ft_strchr(cur->literal, '='))
		{
			s = ft_split(cur->literal, '=');
			if (!s[1])
				s[1] = ft_strdup("");
			add_env(&data->env, s[0], s[1]);
			free(s);
		}
		cur = cur->next;
	}
	return (0);
}
