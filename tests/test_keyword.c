#include "../inc/test.h"

t_lexer	*l = NULL;
t_token	*t = NULL;

Test(lex_keyword, test_invalid_cases)
{
	char *cases[] = {"pwdd", "cdc", "exitt", "dexport", "e", "c", "env$", "echo%", "unset/", 0};

	for (int i = 0; cases[i]; i++)
	{
		l = new_lexer(cases[i]);
        cr_assert_not_null(l, "Failed to create lexer for input: %s", cases[i]);
        t = lex_keyword(l);
        cr_assert_null(t, "Expected a NULL for input: %s", cases[i]);
        free(t);
        free(l);
	}
}

Test(lex_keyword, test_valid_cases) {
    struct {
        const char *input;
        t_token_type type;
    } test_cases[] = {
        {"pwd", PWD},
        {"cd", CD},
        {"export", EXPORT},
        {"unset", UNSET},
        {"env", ENV},
        {"exit", EXIT},
        {"echo", ECHO},
        {"clear", CLEAR},
        {NULL, 0}
    };

    for (int i = 0; test_cases[i].input != NULL; i++) {
        t_lexer *l = new_lexer(test_cases[i].input);
        cr_assert_not_null(l, "Failed to create lexer for input: %s", test_cases[i].input);

        t_token *t = lex_keyword(l);
        cr_assert_not_null(t, "Expected a token for input: %s", test_cases[i].input);

        cr_expect(t->type == test_cases[i].type,
                  "For input '%s', expected type %d but got %d",
                  test_cases[i].input, test_cases[i].type, t->type);

        free(t);
        free(l);
    }
}
