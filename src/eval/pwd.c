/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelnyk <dmelnyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:40:18 by dmelnyk           #+#    #+#             */
/*   Updated: 2025/03/12 12:48:05 by dmelnyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./eval_private.h"
#include <stdio.h>
#include <stdlib.h>

bool	handle_pwd(t_astnode *head, t_data *data)
{
	char	*buf;

	buf = get_curent_dir();
	if (!buf)
		return (1);
	puts(buf);
	free(buf);
	return (0);
}
