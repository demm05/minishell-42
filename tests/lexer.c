#include "../inc/test.h"

t_lexer	*l = NULL;

static void	compare_tokens(t_lexer *l, t_token_type expected_tokens[], int size)
{
	int i = 0;
	t_token	*cur;

	cur = l->tokens;
	while (i < size)
	{
		cr_assert_not_null(cur, "%d node wasn't malloced", i+1);
		cr_expect(cur->type == expected_tokens[i], 
			"%d nodes type should be: %d instead got: (type: %d; size: %d; literal: s)", 
			i+1, expected_tokens[i], cur->type, cur->size);
		cur = cur->next;
		i++;
	}
}

Test(generate_tokens, env_vars_1)
{
	char	*input =	"$ENV $DFF $123 $:DFFD $?";
	t_token_type et[] = {DSIGN, DSIGN, DSIGN, ILLEGAL, EXIT_STATUS, EOL};
	int	size = sizeof(et) / sizeof(et[0]);
	l = new_lexer(input);
	generate_tokens(l);
	compare_tokens(l, et, size);
	free_lexer(l);
}

Test(append_token, basic_1)
{
	t_token	*tok;

	l = new_lexer("");
	cr_assert_not_null(l, "Failed to create basic lexer");
	tok = malloc(sizeof(t_token));
	memset(tok, 0, sizeof(t_token));
	append_token(l, 0, 0);
	cr_assert_not_null(l->tokens, "append_token didn't add node when there wasn't any tokens int the list");
	tok = malloc(sizeof(t_token));
	memset(tok, 0, sizeof(t_token));
	append_token(l, 0, 0);
	cr_assert_not_null(l->tokens, "append_token didn't add node when there is only 1 node in the list");
	tok = malloc(sizeof(t_token));
	memset(tok, 0, sizeof(t_token));
	append_token(l, 0, 0);
	cr_assert_not_null(l->tokens, "append_token didn't add node when there is only 2 nodes in the list");
	free_lexer(l);
}
