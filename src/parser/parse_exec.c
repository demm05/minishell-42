#include "../../inc/parser.h"

t_astnode	*parse_exec(t_token *token)
{
	static t_token_type	end[] = {AND, OR, PIPE};
	static t_token_type	fine[] = {WORD, EXPAND_VAR, PATH};
	static t_token_type	redir[] = {REDIR_IN, REDIR_OUT, REDIR_OUT_A, HERE_DOC};
	t_astnode	*head;

	head = NULL;
	while (token)
	{
		while (match(token, redir, 4))
		{
			token = token->next;
			if (token)
				token = token->next;
		}
		if (!head)
		{
			head = new_astnode(token);
			token = token->next;
			continue ;
		}
		if (!token || match(token, end, 3))
			break ;
		else if (match(token, fine, 3))
			add_child(head, new_astnode(token));
		token = token->next;
	}
	return (head);
}
