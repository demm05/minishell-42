/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelnyk <dmelnyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 18:24:26 by dmelnyk           #+#    #+#             */
/*   Updated: 2025/04/07 18:24:27 by dmelnyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "extra_private.h"
#include <stdarg.h>

static inline void	join_it(char *dest, va_list arg, int num_of_strs)
{
	int		write_index;
	int		read_index;
	char	*s;

	write_index = 0;
	while (num_of_strs--)
	{
		read_index = 0;
		s = va_arg(arg, char *);
		while (s && s[read_index])
			dest[write_index++] = s[read_index++];
	}
	dest[write_index] = 0;
	va_end(arg);
}

static inline int	get_size(va_list arg, int num_of_strs)
{
	int		size;
	va_list	copy;

	size = 0;
	va_copy(copy, arg);
	while (num_of_strs--)
		size += (ft_strlen(va_arg(copy, char *)));
	va_end(copy);
	return (size);
}

char	*join_strings(int num_of_strs, ...)
{
	char	*res;
	va_list	arg;
	int		size;

	va_start(arg, num_of_strs);
	size = get_size(arg, num_of_strs);
	res = malloc(sizeof(char) * (size + 1));
	if (!res)
	{
		va_end(arg);
		return (NULL);
	}
	join_it(res, arg, num_of_strs);
	va_end(arg);
	return (res);
}
