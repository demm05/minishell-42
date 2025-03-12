#include "../inc/test.h"

t_astnode	*head = NULL;

Test(ast, ast_pop_test_1)
{
	t_token	tok;

	tok.type = EOL; 
	tok.literal = NULL;
	head = new_astnode(&tok);
	cr_assert_not_null(head);
	ast_pop(&head->children, NULL);
	tok.type = EXEC;
	add_child(head, new_astnode(&tok));
	cr_assert_not_null(head->children);
	tok.type = ECHO;
	add_child(head, new_astnode(&tok));
	cr_assert_not_null(head->children->next);
	ast_pop(&head->children, &head->children->next);
	cr_expect_null(head->children->next);
	cr_assert_not_null(head->children->prev);
	cr_assert_null(head->children->next);
	cr_expect(head->children->prev->type == EXEC);
	cr_expect(head->children->type == EXEC);
	ast_pop(&head->children, &head->children);
	cr_expect_null(head->children);
	free(head);
}

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
