/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelnyk <dmelnyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:44:14 by dmelnyk           #+#    #+#             */
/*   Updated: 2025/03/12 12:46:08 by dmelnyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./eval_private.h"
#include "../extra/extra.h"
#include <stdio.h>

bool	handle_env(t_astnode *head, t_data *data)
{
	t_env	*env;

	env = data->env;
	while (env)
	{
		printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
	data->exit_status = 0;
	return (0);
}
