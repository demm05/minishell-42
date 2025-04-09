/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelnyk <dmelnyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 18:20:52 by dmelnyk           #+#    #+#             */
/*   Updated: 2025/04/07 18:23:11 by dmelnyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIROMENT_H
# define ENVIROMENT_H

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
	struct s_env	*prev;
}	t_env;

/**
 * @brief Gets an environment variable by key.
 *
 * @param head A pointer to the head of the environment variables list.
 * @param key  The key to search for.
 * @return A pointer to the t_env struct, or NULL if not found.
 */
t_env	*env_get_bykey(t_env *head, char *key);

/**
 * @brief Gets an environment variable's value by key.
 *
 * @param head A pointer to the head of the environment variables list.
 * @param key  The key to search for.
 * @return A pointer to the value (not malloced), or NULL if not found.
 */
char	*env_get_value(t_env *head, char *key);

/**
 * @brief Adds an environment variable to the list.
 *
 * @param head  A pointer to the head of the env list (double pointer).
 * @param key   The malloced key of the variable.
 * @param value The malloced value of the variable.
 * @return A pointer to the new t_env node, or NULL on failure.
 */
t_env	*env_add(t_env **head, char *key, char *value);

/**
 * @brief Frees the environment variables list.
 *
 * @param head A double pointer to the head of the list.
 */
void	env_free(t_env **head);

/**
 * @brief Initializes the environment variables.
 *
 * @param argv The argument vector.
 * @param envp The environment variables array.
 * @return A pointer to the head of the environment variables list.
 */
t_env	*env_init(char **argv, char **envp);

/*
* @brief Free enviroment node if found
*/
void	env_unset(t_env **env, char *key);

/*
 * Builds an environment variable array suitable for use with execve.
 * Takes a linked list of environment variables ('t_env') and converts it
 * into a dynamically allocated, NULL-terminated array of strings, where each
 * string is in the format "key=value".
 */
char	**env_create_arr(t_env *env);

// @brief Calucates num of node in env list
int		env_getsize(t_env *env);

//@brief Return a copy of valid env key from a string
char	*env_get_key(const char *s);

void	env_arr_free(char **arr);

/**
 * Increments the shell level in environment variables
 * Handles edge cases like invalid SHLVL values
 *
 * @param shlvl Pointer to the SHLVL environment variable
 */
void	increment_shlvl(t_env *shlvl);

#endif
