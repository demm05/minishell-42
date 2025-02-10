#include "../inc/test.h"

t_lexer	*l = NULL;

Test(new_token, creating_new_token)
{
	t_token	*tok;

	tok = new_token(PIPE, NULL, 1);
	cr_expect_null(tok->literal);
	free(tok);
	tok = new_token(PIPE, "HELLO", 1);
	cr_expect(strcmp(tok->literal, "HELLO") == 0);
	free(tok->literal);
	free(tok);
}

Test(new_lexer, initalize)
{
	l = new_lexer("cd /bin/ls | echo \"Hello world\"");
	cr_expect_not_null(l, "Lexer should be initialized");
	cr_expect(l->read_postion == 1);
	cr_expect(l->pos == 0);
	cr_expect(l->size == 31);
	cr_expect(l->ch == 'c');
	free(l);
	cr_expect_null(new_lexer(NULL), "new_lexer(null) should return null");
	l = new_lexer("");
	cr_expect_not_null(l, "new_lexer(\"\") should not return NULL");
	cr_expect(strlen(l->input) == 0);
	free(l);
}

Test(get_next_token, single_literal)
{
	t_token	tests[] = {
		{LBRACE, "{"},
		{RBRACE, "}"},
		{LPAREN, "("},
		{RPAREN, ")"},
		{SQUOTE, "'"},
		{DQUOTE, "\""},
		{PIPE, "|"},
		{LT, "<"},
		{GT, ">"},
		{DLT, "<<"},
		{DGT, ">>"},
		{EOL, NULL} 
	};
	int	n = sizeof(tests) / sizeof(tests[0]) - 1;
	t_token	*t;
	int	i = -1;


	while (++i < n)
	{
		l = new_lexer(tests[i].literal);
		t = get_next_token(l);
		cr_expect(tests[i].type == t->type, "test: %d\tI shoul've get type %s(%d) but got %d", i, tests[i].literal, tests[i].type, t->type);
		free(t);
		free(l);
	}
}

Test(get_next_token, single_literal_whitespaces)
{
	t_token	tests[] = {
		{LBRACE, "  \t {    \t"},
		{RBRACE, "  \r \r } \t"},
		{LPAREN, "\t (\t       "},
		{RPAREN, "\r ) \r\r   "},
		{SQUOTE, "'   \t\t\t"},
		{DQUOTE, "\t\t\t     \" "},
		{PIPE, "\t\t  |  "},
		{LT, "  \t <  "},
		{GT, "   >   \t"},
		{DLT, "     << \t   "},
		{DGT, "    >>   "},
		{EOL, NULL} 
	};
	int	n = sizeof(tests) / sizeof(tests[0]) - 1;
	t_token	*t;
	int	i = -1;


	while (++i < n)
	{
		l = new_lexer(tests[i].literal);
		t = get_next_token(l);
		cr_expect(tests[i].type == t->type, "test: %d\tI shoul've get type %d but got %d", i, tests[i].type, t->type);
		free(t);
		t = get_next_token(l);
		cr_expect(EOL == t->type, "test: %d\tI shoul've get EOL", i);
		free(t);
		free(l);
	}
}
