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

Test(ast, ast_pop_head)
{
	t_token	tok;

	tok.type = EOL; 
	tok.literal = NULL;
	head = new_astnode(&tok);
	cr_assert_not_null(head);
	tok.type = EXEC;
	add_child(head, new_astnode(&tok));
	cr_assert_not_null(head->children);
	ast_pop(&head->children, &head->children);
	cr_expect_null(head->children);
	free(head);
}

Test(ast, ast_pop_last)
{
	t_token	tok;

	tok.type = EOL; 
	tok.literal = NULL;
	head = new_astnode(&tok);
	cr_assert_not_null(head);
	tok.type = EXEC;
	add_child(head, new_astnode(&tok));
	cr_assert_not_null(head->children);
	tok.type = DQUOTE;
	add_child(head, new_astnode(&tok));
	cr_assert_not_null(head->children->next);
	ast_pop(&head->children, &head->children->next);
	cr_expect_null(head->children->next);
	cr_expect_not_null(head->children->prev);
	cr_expect(head->children->prev->type == EXEC);
	free(head->children);
	free(head);
}

Test(ast, ast_pop_mid)
{
	t_token	tok;

	tok.type = EOL; 
	tok.literal = NULL;
	head = new_astnode(&tok);
	cr_assert_not_null(head);
	tok.type = ECHO;
	add_child(head, new_astnode(&tok));
	cr_assert_not_null(head->children);
	tok.type = DQUOTE;
	add_child(head, new_astnode(&tok));
	tok.type = EXEC;
	add_child(head, new_astnode(&tok));
	ast_pop(&head->children, &head->children->next);
	cr_assert_not_null(head->children);
	cr_assert_not_null(head->children->prev);
	cr_assert_not_null(head->children->next);
	cr_expect(head->children->type == ECHO);
	cr_expect(head->children->next->type == EXEC);
	cr_expect(head->children->prev->type == EXEC);
	cr_expect_null(head->children->next->next);
	free(head->children->prev);
	free(head->children);
	free(head);
}
