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

# include "./extra.h"

typedef struct s_quote_state
{
	bool	escape;
	bool	in_squote;
	bool	in_dquote;
	int		in_parentheses;
}	t_quote_state;

/**
 * @brief Reads a full line, handling multi-line continuation.
 *
 * @param data  A pointer to the t_data structure.
 * @param state A pointer to the quote state.
 */
void	read_full_line(t_data *data, t_quote_state *state);

/**
 * @brief Initializes the environment variables.
 *
 * @param argv The argument vector.
 * @param envp The environment variables array.
 * @return A pointer to the head of the environment variables list.
 */
t_env	*init_env(char **argv, char **envp);

#endif
