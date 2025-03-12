/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelnyk <dmelnyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:37:12 by dmelnyk           #+#    #+#             */
/*   Updated: 2025/03/12 15:47:28 by dmelnyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXTRA_H 
# define EXTRA_H 

# include "../../inc/minishell.h"
# include <stdbool.h>

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
	struct s_env	*prev;
}	t_env;

bool	ft_isspace(char ch);

/**
 * @brief Gets an environment variable by key.
 *
 * @param head A pointer to the head of the environment variables list.
 * @param key  The key to search for.
 * @return A pointer to the t_env struct, or NULL if not found.
 */
t_env	*getenv_val(t_env *head, char *key);

/**
 * @brief Appends an environment variable to the list.
 *
 * @param head  A pointer to the head of the env list (double pointer).
 * @param key   The key of the variable.
 * @param value The value of the variable.
 * @return A pointer to the new t_env node, or NULL on failure.
 */
t_env	*append_env(t_env **head, char *key, char *value);

/**
 * @brief Frees the environment variables list.
 *
 * @param head A double pointer to the head of the list.
 */
void	free_env(t_env **head);

/**
 * @brief Gets the current working directory.
 * @return The current working directory, or NULL on error. Caller must free.
 */
char	*get_curent_dir(void);

/**
 * @brief Initializes the main data structure.
 *
 * @param argc The argument count.
 * @param argv The argument vector.
 * @param envp The environment variables.
 * @return A pointer to the initialized t_data structure, or NULL on error.
 */
t_data	*init(int argc, char **argv, char **envp);

/**
 * @brief Frees a t_data structure and its contents.
 *
 * @param data A pointer to the t_data structure.
 * @return Always 0.
 */
int		free_data(t_data *data);

#endif
