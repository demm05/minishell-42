/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelnyk <dmelnyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:40:03 by dmelnyk           #+#    #+#             */
/*   Updated: 2025/03/12 12:46:10 by dmelnyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./eval_private.h"
#include <stdlib.h>

static bool					is_redir(t_token_type type);

void	exec(t_data *data)
{
	if (!data->head)
		return ;
	eval(data->head, data);
}

bool	eval(t_astnode *head, t_data *data)
{
	if (head->type == AND)
	{
		if (eval(head->children, data))
			return (1);
		if (eval(head->children->next, data))
			return (1);
	}
	if (head->type == OR)
	{
		if (!eval(head->children, data))
			return (0);
		if (!eval(head->children->next, data))
			return (0);
		return (1);
	}
	if (head->type == EXEC)
		return (handle_exec(head, data));
	if (is_built_in(head->type))
		return(is_built_in(head->type)(head, data));
	if (is_redir(head->type))
		return (handle_redir(head, data));
	if (head->type == PIPE)
		return (handle_pipe(head, data));
	return (1);
}

/*
 * Checks if a given token type represents a redirection operation.
 *
 * @param type The token type to check.
 * @return `true` if the token is a redirection operator, `false` otherwise.
 */
static bool	is_redir(t_token_type type)
{
	if (type == REDIR_IN)
		return (true);
	if (type == REDIR_OUT)
		return (true);
	if (type == REDIR_OUT_A)
		return (true);
	if (type == HERE_DOC)
		return (true);
	return (false);
}

/*
 * Returns a function pointer to the appropriate built-in command handler.
 *
 * Given a token type representing a built-in command (e.g., ECHO, CD, PWD),
 * this function returns a pointer to the corresponding handler function
 * (e.g., handle_echo, handle_cd, handle_pwd).
 *
 * @param type The token type of the built-in command.
 * @return A function pointer to the built-in handler, or NULL if the type
 *         does not correspond to a built-in command.  The returned function
 *         pointer is of type `builtin_func_ptr`, which is presumably defined
 *         elsewhere as `bool (*builtin_func_ptr)(t_astnode *, t_data *)`.
 */
t_builtin_func_ptr is_built_in(t_token_type type)
{
	if (type == ECHO)
		return (handle_echo);
	if (type == CD)
		return (handle_cd);
	if (type == PWD)
		return (handle_pwd);
	if (type == EXPORT)
		return (handle_export);
	if (type == UNSET)
		return (handle_unset);
	if (type == EXIT)
		return (handle_exit);
	if (type == ENV)
		return (handle_env);
	return (NULL);
}
