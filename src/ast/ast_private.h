/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_private.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelnyk <dmelnyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:30:41 by dmelnyk           #+#    #+#             */
/*   Updated: 2025/03/12 12:34:44 by dmelnyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_PRIVATE_H
# define AST_PRIVATE_H

# include "./ast.h"

t_astnode	*new_astnode(t_token *tok);
void		add_child(t_astnode *parent, t_astnode *child);
bool		match(t_token *token, t_token_type expected[], int size);

t_astnode	*parse_exec(t_token *token);
t_astnode	*parse_redir(t_token **token);
t_astnode	*parse_logical_exp(t_token **token);
t_astnode	*parse_pipe(t_token **token);

#endif
