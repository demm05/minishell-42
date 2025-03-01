#include "../inc/test.h"

t_lexer	*l = NULL;

Test(lex_quote, double_test_1)
{
	l = new_lexer("\"Hello $SHELL TEST \"");
	cr_assert_not_null(l);
	lex_quote(l);
	cr_assert_not_null(l->tokens);
	cr_expect(l->tokens->type == WORD);
	cr_assert_not_null(l->tokens->next);
	cr_expect(l->tokens->next->type == EXPAND_VAR);
	cr_assert_not_null(l->tokens->next->next);
	cr_expect(l->tokens->next->next->type == WORD);
}

Test(lex_quote, single_test_1)
{
	char	*s = "'Hello $SHELL TEST '";

	l = new_lexer(s);
	cr_assert_not_null(l);
	lex_quote(l);
	cr_assert_not_null(l->tokens);
	cr_assert_null(l->tokens->next);
	cr_expect((unsigned int)l->tokens->size == strlen(s) - 2);
	lex_quote(l);
}
