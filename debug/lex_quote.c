#include "parser.h"

/*
int	main(void)
{
	t_lexer	*l = NULL;
	char	*s = "echo \"HELLO $SHELL\" 'HOW ARE $YOU?' ";
	t_token	*t;

	l = new_lexer(s);
	generate_tokens(l);
	if (l->tokens)
	{
		t = l->tokens;
		while (t)
		{
			int i = 0;
			while (i < t->size)
				printf("%c", t->literal[i++]);
			printf(" -> ");
			t = t->next;
		}
	}
	else
		printf("Error got null\n");
	free_lexer(l);
}
*/
