/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dirs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelnyk <dmelnyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:40:14 by dmelnyk           #+#    #+#             */
/*   Updated: 2025/03/12 12:00:54 by dmelnyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <unistd.h>

char	*get_curent_dir(void)
{
	return (getcwd(NULL, 0));
}
