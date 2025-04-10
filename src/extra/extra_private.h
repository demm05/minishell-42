/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_private.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelnyk <dmelnyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:41:12 by dmelnyk           #+#    #+#             */
/*   Updated: 2025/03/12 15:46:35 by dmelnyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXTRA_PRIVATE_H 
# define EXTRA_PRIVATE_H

# include "minishell.h"

# define RED "\001\033[1;31m\002"
# define GREEN "\001\033[1;32m\002"
# define RESET "\001\033[0m\002"

typedef struct s_read_state
{
	char	*line;
	char	*cont;
	int		in_parentheses;
	bool	in_squote;
	bool	in_dquote;
	bool	escape;
}	t_read_state;

#endif
