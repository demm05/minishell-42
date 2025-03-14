/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval_private.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelnyk <dmelnyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:27:19 by dmelnyk           #+#    #+#             */
/*   Updated: 2025/03/14 15:47:25 by dmelnyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVAL_PRIVATE_H
# define EVAL_PRIVATE_H

# include <stdbool.h>
# include "libft.h"
# include "./eval.h"
# include "../ast/ast.h"
# include "../extra/extra.h"

typedef bool			(*t_builtin_func_ptr)(t_astnode *head, t_data *data);

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

void	expand_tree(t_astnode *parent, t_data *data);
void	exec_command(t_astnode *head, t_data *data);

#endif
