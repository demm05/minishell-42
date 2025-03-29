/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelnyk <dmelnyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:40:03 by dmelnyk           #+#    #+#             */
/*   Updated: 2025/03/22 19:34:28 by dmelnyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./eval_private.h"
#include "../expansion/expansion.h"
#include <stdlib.h>

static inline bool	evaluate_logical_exp(t_astnode *head, t_data *data);

void	exec(t_data *data)
{
	if (!data || !data->head)
		return ;
	eval(data->head, data);
}

bool	eval(t_astnode *head, t_data *data)
{
	bool	s;

	s = 1;
	if (head->type == AND || head->type == OR)
		s = evaluate_logical_exp(head, data);
	expand_head(head, data);
	if (head->type == EXEC)
		s = handle_exec(head, data);
	if (is_built_in(head->type))
		s = is_built_in(head->type)(head, data);
	if (head->type == PIPE)
		s = handle_pipe(head, data);
	if (is_redir(head->type))
		s = handle_redir(head, data);
	if (head->next && head->type != AND && head->type != OR)
		s = eval(head->next, data);
	return (s);
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

static inline bool	evaluate_logical_exp(t_astnode *head, t_data *data)
{
	bool	status;

	expand_head(head->children, data);
	status = eval(head->children, data);
	if (status && head->type == AND)
		return (1);
	else if (!status && head->type == OR)
		return (0);
	expand_head(head->children->next, data);
	status = eval(head->children->next, data);
	return (status);
}
