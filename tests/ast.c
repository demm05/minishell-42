/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelnyk <dmelnyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 14:07:42 by dmelnyk           #+#    #+#             */
/*   Updated: 2025/03/14 14:07:43 by dmelnyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/test.h"

t_astnode	*head = NULL;
char		*argv[] = {"./minishell"};

Test(ast, add_child_test_1)
{
	t_token	tok;

	tok.type = EOL; 
	tok.literal = NULL;
	head = new_astnode(&tok);
	cr_assert_not_null(head);
	add_child(head, new_astnode(&tok));
	cr_assert_not_null(head->children);
	cr_assert_not_null(head->children->prev);
	cr_expect_null(head->children->next);
	cr_expect(head->children->prev->type == EOL);
	tok.type = EXEC; 
	add_child(head, new_astnode(&tok));
	cr_assert_not_null(head->children);
	cr_assert_not_null(head->children->next);
	cr_assert_not_null(head->children->prev);
	cr_expect_null(head->children->prev->next);
	cr_expect(head->children->prev->type == EXEC);
	free_ast(&head);
}

Test(ast, new_astnode_test1)
{
	t_token	tok;

	tok.type = EOL; 
	tok.literal = NULL;
	head = new_astnode(&tok);	
	cr_assert_not_null(head);
	cr_expect_null(head->prev);
	cr_expect_null(head->next);
	cr_expect(head->type == EOL);
	cr_assert_null(head->literal);
}
