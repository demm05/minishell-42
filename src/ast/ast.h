/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelnyk <dmelnyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 11:15:42 by dmelnyk           #+#    #+#             */
/*   Updated: 2025/03/14 14:05:09 by dmelnyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include "../../inc/minishell.h"
# include "../lexer/lexer.h"

typedef struct s_astnode
{
	struct s_astnode	*next;
	struct s_astnode	*prev;
	struct s_astnode	*children;
	char				*literal;
	int					childs;
	t_token_type		type;
}	t_astnode;

t_astnode	*parse(t_lexer *l);
void		print_ast(t_astnode *node, int depth);
void		free_ast(t_astnode **node);

/**
 * @brief Removes a node from the AST.
 *
 * @param head A double pointer to the head of the AST.
 * @param node A double pointer to the node to be removed.
 */
void		ast_pop(t_astnode **head, t_astnode **node);
void		add_child(t_astnode *parent, t_astnode *child);

#endif
