/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelnyk <dmelnyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:37:12 by dmelnyk           #+#    #+#             */
/*   Updated: 2025/03/11 17:29:27 by dmelnyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "../../inc/parser.h"
# include "../../inc/exec.h"

typedef struct s_quote_state
{
	bool	escape;
	bool	in_squote;
	bool	in_dquote;
	int		in_parentheses;
}	t_quote_state;

void	read_full_line(t_data *data, t_quote_state *state);

#endif
