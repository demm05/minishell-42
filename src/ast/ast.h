/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelnyk <dmelnyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 11:15:42 by dmelnyk           #+#    #+#             */
/*   Updated: 2025/03/22 11:28:15 by dmelnyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include "../../inc/minishell.h"
# include "../tokenize_line/tok.h"

typedef struct s_astnode
{
	int					childs;
	t_token_type		type;
	char				*literal;
	struct s_astnode	*children;
	struct s_astnode	*parent;
	struct s_astnode	*next;
	struct s_astnode	*prev;
}	t_astnode;

void		create_ast(t_data *data);
void		print_ast(t_astnode *node, int depth);
void		free_ast(t_astnode **node);
void		add_child(t_astnode *parent, t_astnode *child);
t_astnode	*new_astnode(t_token *tok);
void		assemble_head(t_astnode *head, t_data *data);

t_astnode	*append_astnode(t_astnode **head, t_astnode *new);

#endif
