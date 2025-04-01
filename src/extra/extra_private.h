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

typedef struct	s_read_state
{
	char	*line;
	char	*cont;
	int		in_parentheses;
	bool	in_squote;
	bool	in_dquote;
	bool	escape;
}	t_read_state;

/**
 * @brief Initializes the environment variables.
 *
 * @param argv The argument vector.
 * @param envp The environment variables array.
 * @return A pointer to the head of the environment variables list.
 */
t_env	*init_env(char **argv, char **envp);
t_env	*append_env(t_env **head, char *key, char *value);

#endif
