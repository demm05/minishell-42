#include "../../inc/parser.h"

t_astnode	*parse_redir(t_token **token)
{
	static t_token_type	expected[] = {REDIR_OUT, REDIR_OUT_A, REDIR_IN, HERE_DOC};
	static t_token_type	end[] = {AND, OR, PIPE, EOL};
	t_astnode			*left;	
	t_astnode			*head;
	t_astnode			*temp;

	left = parse_exec(*token);
	if (!left)
		return (NULL);
	head = NULL;
	while (*token)
	{
		if (!match(*token, expected, 4))
		{
			if (match(*token, end, 4))
				break ;
			*token = (*token)->next;
			continue ;
		}
		if (head)
		{
			temp = new_astnode(*token);	
			add_child(temp, head);
			head = temp;
		}
		else
			head = new_astnode(*token);
		*token = (*token)->next;
		if (!*token || match(*token, end, 4))
		{
			free_ast(&head);
			free_ast(&left);
			printf("syntax error unexpected token: %s\n", decode((*token)->type));
			break ;
		}
		(*token)->type = PATH;
		add_child(head, new_astnode(*token));
		*token = (*token)->next;
	}
	if (!head)
		return (left);
	add_child(head, left);
	return (head);
}
