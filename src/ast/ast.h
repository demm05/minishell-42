/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelnyk <dmelnyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 11:15:42 by dmelnyk           #+#    #+#             */
/*   Updated: 2025/04/07 18:23:03 by dmelnyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include "../lexer/lexer.h"

typedef struct s_data		t_data;

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

int			ast_get_size(t_astnode *head);
void		create_ast(t_data *data);
void		print_ast(t_astnode *node, int depth);
void		free_ast(t_astnode **node);
void		add_child(t_astnode *parent, t_astnode *child);
t_astnode	*new_astnode(t_token *tok);
void		assemble_head(t_astnode *head, t_data *data);

t_astnode	*append_astnode(t_astnode **head, t_astnode *new);
void		ast_delete_first_child(t_astnode *parent);

#endif
