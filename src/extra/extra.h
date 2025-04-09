/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelnyk <dmelnyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:37:12 by dmelnyk           #+#    #+#             */
/*   Updated: 2025/04/08 17:18:01 by dmelnyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXTRA_H 
# define EXTRA_H 

# include <stdbool.h>

typedef struct s_astnode	t_astnode;
typedef struct s_data		t_data;
typedef struct s_env		t_env;

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
t_data	*init(char **argv, char **envp);

/**
 * @brief Frees a t_data structure and its contents.
 *
 * @param data A pointer to the t_data structure.
 * @return Always 0.
 */
int		free_data(t_data *data);

void	set_signal(int sig);
int		get_signal(void);
void	interactive_read(t_data *data);
char	*mini_readline(char *prompt, bool complete_state);
int		get_childs_status(int status);
char	*join_strings(int num_of_strs, ...);
int		free_everything(t_data *data);
char	*get_path(t_env *env, char *literal, t_data *data);
char	**dir_get_content_list(char *pwd);
void	dir_free_list(char **l);
void	update_prompt(t_data *data);

#endif
