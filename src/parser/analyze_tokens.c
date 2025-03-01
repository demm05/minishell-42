#include "../../inc/parser.h"

void	show_where_illegal(t_token *ileg, t_lexer *l)
{
	int	i;
	int	len;

	printf("%s\n", l->input);
	len = ileg->literal - l->input;
	i = 0;
	while (i++ < len)
		printf(" ");
	printf("^\n");
	i = 0;
	while (i++ < len)
		printf(" ");
	printf("illegal token type\n");
}

int	analyze_tokens(t_lexer *l)
{
	t_token	*token;

	token = l->tokens;
	while (token)
	{
		if (token->type == ILLEGAL)
		{
			show_where_illegal(token, l);
			return (1);
		}
		else if (token->type == REDIR_OUT || token->type == REDIR_OUT_A || token->type == REDIR_IN)
			if (token->next->type == EOL)
				return (2);
		token = token->next;
	}
	return (0);
}
