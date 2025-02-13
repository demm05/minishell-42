#include "../inc/test.h"

t_lexer	*l = NULL;

Test(lex_env_var, extra_1)
{
	t_token	*t;

	l = new_lexer("$0$111$?");
	cr_assert_not_null(l);
	t = lex_env_var(l);
	cr_expect(t->type == DSIGN, "Expected %d got %d %s", ILLEGAL, t->type, t->literal);
	free(t);
	t = lex_env_var(l);
	cr_expect(t->type == DSIGN, "Expected %d got %d %s", DSIGN, t->type, t->literal);
	free(t);
	t = lex_env_var(l);
	cr_expect(t->type == EXIT_STATUS, "Expected %d got %d %s", DSIGN, t->type, t->literal);
	free(t);
	free(l);
}

Test(lex_env_var, valid_whitespaces)
{
	char	*str = "$PATH $Path   $HOME_HOME $TES_T $R__EST $HE123 $h_1";
	t_token	*tok;
	char	**vars;
	int		i = 0;
	
	vars = ft_split(str, ' ');
	l = new_lexer(str);
	while (vars[i])
	{
		eat_whitespaces(l);
		tok = lex_env_var(l);
		cr_assert_not_null(tok, "Failed on initializing env token, current lexer input: %s", l->input + l->position);
		cr_expect(strncmp(vars[i] + 1, tok->literal, strlen(vars[i]) - 1) == 0, "Expecetd %s got size:%d and s:%s", vars[i]+1, tok->size, tok->literal);
		cr_expect(tok->type == DSIGN, "%d: Expected typed: %d insteadt got %d", i, DSIGN, tok->type);
		free(tok);
		free(vars[i]);
		i++;
	}
	free(l);
	free(vars);
}

Test(lex_env_var, invalid)
{
	t_token	*tok;
	char	*tests[] = {"$;", "$!1HE123", "$!te__1", NULL};
	int		i = 0;

	while (tests[i])
	{
		l = new_lexer(tests[i]);
		tok = lex_env_var(l);
		cr_assert_not_null(tok);
		cr_expect(tok->type == ILLEGAL, "Invalid token type for %d expected %d got %d", i, ILLEGAL, tok->type);
		cr_expect(strlen(tests[i]) == (size_t)tok->size, 
			"%d Invalid size of returned token literal Expecetd: %d %s got %d %s", 
			i, strlen(tests[i]), tests[i], tok->size, tok->literal);
		cr_expect_null(l->ch, "Lexer should be moved to the end of str, current pos: %d %c", l->position, l->ch);
		free(tok);
		free(l);
		i++;
	}
}

Test(lex_env_var, invalid_whitespaces)
{
	t_token	*tok;
	char	*tests[] = {"$%123   ", "$,1HE123   ", "$!te__1   ", NULL};
	int		i = 0;
	char	*temp;

	while (tests[i])
	{
		l = new_lexer(tests[i]);
		tok = lex_env_var(l);
		cr_expect(tok->type == ILLEGAL, "Invalid token type for %d expected %d got %d", i, ILLEGAL, tok->type);
		temp = ft_strtrim(tests[i], " \t\r\n");
		cr_expect(strlen(temp) == (size_t)tok->size, 
			"%d Invalid size of returned token literal Expecetd: %d %s got %d %s", 
			i, strlen(temp), temp, tok->size, tok->literal);
		cr_expect(ft_isspace(l->ch), "Lexer should be moved to the next whitespace, current pos: %d %c", l->position, l->ch);
		free(temp);
		free(tok);
		free(l);
		i++;
	}
}
