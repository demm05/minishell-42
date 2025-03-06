#ifndef EINTERNAL_H
# define EINTERNAL_H

# include "./types.h"

/**
 * @brief Main execution function, initiates the evaluation of the AST.
 *
 * @param data The main data structure for the shell.
 * @note This function serves as the entry point for command execution.
 */
void	exec(t_data *data);

/**
 * @brief Recursively evaluates the abstract syntax tree (AST).
 *
 * This function traverses the AST, handling different node types
 * (AND, OR, EXEC, built-ins, redirections, pipes) and executing
 * the corresponding actions.  It implements the core logic of the shell's
 * command execution.
 *
 * @param head The current node of the AST being evaluated.
 * @param data The main data structure for the shell.
 * @return `true` if the evaluation should continue, 
 * 		`false` otherwise (e.g., on error or exit condition).
 */
bool	eval(t_astnode *head, t_data *data);

// Built in functions for execution
bool	handle_cd(t_astnode *head, t_data *data);
bool	handle_echo(t_astnode *head, t_data *data);
bool	handle_pwd(t_astnode *head, t_data *data);
bool	handle_env(t_astnode *head, t_data *data);
bool	handle_unset(t_astnode *head, t_data *data);
bool	handle_exit(t_astnode *head, t_data *data);
bool	handle_export(t_astnode *head, t_data *data);
bool	handle_exec(t_astnode *head, t_data *data);
bool	handle_pipe(t_astnode *head, t_data *data);
bool	handle_redir(t_astnode *head, t_data *data);
// Built in functions for execution

// ===========================ENV===========================
/**
 * Initializes environment list with envp and default env variables
 *
 * @param envp Environment variables array from main
 * @param argv Arguments array from main
 * @return Pointer to the head of the environment list
 */
t_env	*init_env(char **argv, char **envp);

/**
 * Searches the environment list for a specific key
 *
 * @param head Pointer to the head of the environment list
 * @param key  The environment variable key to search for
 * @return     Pointer to the found environment variable or NULL if not found
 */
t_env	*getenv_val(t_env *head, char *key);

/**
 * Appends a new environment variable to the environment list
 * 
 * Adds a new key-value pair to the environment list using a circular
 * doubly linked list structure. Takes ownership of key and value pointers.
 *
 * @param head  Double pointer to the head of the environment list
 * @param key   Allocated string containing the environment variable key
 * @param value Allocated string containing the environment variable value
 * @return      Pointer to the newly created environment variable 
 * 			or NULL on failure
 */
t_env	*append_env(t_env **head, char *key, char *value);

/**
 * Frees all memory associated with the environment list
 * 
 * Deallocates the entire environment list and sets the head pointer to NULL.
 * This frees each key, value, and node structure.
 *
 * @param head Double pointer to the head of the environment list
 */
void	free_env(t_env **head);
// ===========================ENV===========================

/**
 * Gets the current working directory
 * 
 * Uses getcwd with NULL buffer to have the system allocate memory.
 * The caller is responsible for freeing the returned string.
 *
 * @return Dynamically allocated string containing current working directory
 */
char	*get_curent_dir(void);

#endif
