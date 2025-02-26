#include "../../inc/parser.h"

t_astnode	*parse_and(t_token *token);

int	analyze_tokens(t_token *token)
{
	while (token)
	{
		if (token->type == ILLEGAL)
			return (1);
		else if (token->type == REDIR_OUT || token->type == REDIR_OUT_A || token->type == REDIR_IN)
			if (token->next->type == EOL)
				return (2);
		token = token->next;
	}
	return (0);
}

void	parse(char *line)
{
	t_lexer	*l;
	int		status;

	l = new_lexer(line);
	generate_tokens(l);
	status = analyze_tokens(l->tokens);
	if (!status)
	{
		printf("Error syntax error: %d\n", status);
	}
	else
		parse_and(l->tokens);
}

t_astnode	*parse_logical_exp(t_token *token)
{

}

t_astnode	*parse_pipe(t_token *token)
{
	t_astnode	*left;	

	left = parse_exec(token);
}

t_astnode	*parse_and(t_token *token)
{
	t_astnode	*left;	

	left = parse_pipe(token);
}
