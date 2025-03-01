#include "../../inc/parser.h"

t_astnode	*parse_logical_exp(t_token **token);
t_astnode	*parse_pipe(t_token **token);

t_astnode	*parse(t_lexer *l)
{
	t_token		*t_head;
	t_astnode	*head;
	int			status;

	if (!l || !l->tokens)
	{
		free_lexer(l);
		return (NULL);
	}
	status = analyze_tokens(l);
	if (status)
	{
		free_lexer(l);
		return (NULL);
	}
	t_head = l->tokens;
	head = parse_logical_exp(&t_head);
	if (!head)
	{
		free_lexer(l);
		return (NULL);
	}
	return (head);
}

t_astnode	*parse_logical_exp(t_token **token)
{
	static	t_token_type	exp[] = {AND, OR};
	t_astnode	*left;	
	t_astnode	*head;

	left = parse_pipe(token);
	if (match(*token, exp, 2))
	{
		head = new_astnode(*token);
		*token = (*token)->next;
		add_child(head, left);
		add_child(head, parse_logical_exp(token));
		return (head);
	}
	return (left);
}

t_astnode	*parse_pipe(t_token **token)
{
	t_astnode	*left;	
	t_astnode	*head;

	left = parse_exec(token);
	if ((*token)->type == PIPE)
	{
		head = new_astnode(*token);
		*token = (*token)->next;
		add_child(head, left);
		add_child(head, parse_pipe(token));
		return (head);
	}
	return (left);
}
