#include "../inc/test.h"

t_lexer	*l = NULL;
t_astnode	*node = NULL;

Test(utils, new_astnode)
{
	t_astnode	*n;
	t_token		tok;

	ft_memset(&tok, 0, sizeof(tok));
	tok.size = 10;
	tok.type = 11;
	n = new_astnode(&tok);
	cr_assert_not_null(n);
	cr_expect(n->childs == 0);
	cr_expect(n->lit_size == 10);
	cr_expect(n->children == NULL);
	cr_expect(n->type == 11);
	free(n);
}

Test(utils, add_child)
{
	t_astnode	*n;
	t_token		*t;

	l = new_lexer("HELLO WORLD");
	cr_assert_not_null(l);
	t = new_token(AND, l, 1);
	n = new_astnode(t);
	cr_expect(n->type == AND);
	free(t);
	cr_assert_not_null(n);
	t = new_token(EXEC, l, 1);
	add_child(n, new_astnode(t));
	cr_expect(n->children[0]->type == EXEC);
	free(t);
	cr_expect(n->childs == 1);
	t = new_token(EXEC, l, 1);
	add_child(n, new_astnode(t));
	cr_expect(n->children[0]->type == EXEC);
	free(t);
	cr_expect(n->childs == 2);
	t = new_token(WORD, l, 1);
	add_child(n->children[0], new_astnode(t));
	cr_expect(n->children[0]->children[0]->type == WORD);
	free(t);
	cr_expect(n->childs == 2);
	free(l);
	free(n->children[0]->children[0]);
	free(n->children[0]);
	free(n->children[1]);
	free(n);
}

Test(parse, analyze_tokens)
{
	char	*s;

	s = ">>   ";
	l = new_lexer(s);	
	cr_assert_not_null(l);
	generate_tokens(l);
	cr_assert_not_null(l->tokens, "Failed to generate tokens");
	cr_expect(analyze_tokens(l->tokens) != 0, "I expected to get analyze status error for: '%s'", s); 
	free_lexer(l);
}

Test(parse, parse_exec_1)
{
	l = new_lexer("echo $? env >> t");	
	cr_assert_not_null(l);
	generate_tokens(l);
	node = parse_exec(l->tokens);
	cr_assert_not_null(node);
	cr_expect(node->type == ECHO);
	cr_expect(node->childs == 4, "expected: %d childs intsead got: %d", 4, node->childs);
	print_ast(node, 0);
	free_lexer(l);
}
