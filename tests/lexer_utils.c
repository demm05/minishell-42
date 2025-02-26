#include "../inc/test.h"

t_lexer	*l = NULL;

Test(new_token, creating_new_token)
{
	t_token	*tok;

	tok = new_token(PIPE, NULL, 1);
	cr_expect_null(tok, "Expected NULL when passed NULL as lexer");
	l = new_lexer("echo");
	tok = new_token(ECHO, l, 4);
	cr_expect(strncmp(tok->literal, "echo", 4) == 0);
	free(tok);
	free(l);
}

Test(new_token, test_next_post)
{
	t_token	*tok;

	l = new_lexer("echotest");
	tok = new_token(ECHO, l, 4);
	cr_expect(strncmp(tok->literal, "echo", 4) == 0);
	cr_expect(l->ch == 't', "expected t got %c", l->ch);
	free(tok);
	free(l);
}

Test(new_lexer, initalize)
{
	l = new_lexer("cd /bin/ls | echo \"Hello world\"");
	cr_expect_not_null(l, "Lexer should be initialized");
	cr_expect(l->read_postion == 1);
	cr_expect(l->position == 0);
	cr_expect(l->size == 31);
	cr_expect(l->ch == 'c');
	free(l);
	cr_expect_null(new_lexer(NULL), "new_lexer(null) should return null");
	l = new_lexer("");
	cr_expect_not_null(l, "new_lexer(\"\") should not return NULL");
	cr_expect(strlen(l->input) == 0);
	free(l);
}

Test(eat_whitespaces, first)
{
	l = new_lexer("       \t\t \rD");
	cr_assert_not_null(l, "Failed on initializing new lexer");
	eat_whitespaces(l);
	cr_expect(l->ch == 'D', "Failed basic test");
	free(l);
}

Test(is_there_exec, first)
{
	l = new_lexer("HELLO");
	cr_assert_not_null(l);
	append_token(l, REDIR_OUT, 1);
	append_token(l, WORD, 1);
	cr_expect(is_there_exec(l) == 0);
	free_lexer(l);
}
