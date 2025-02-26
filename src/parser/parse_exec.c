#include "../../inc/parser.h"

bool	consume_redir(t_astnode **parent, t_token **token);
bool	consume_exec_args(t_astnode *parent, t_token **token);

t_astnode	*parse_exec(t_token *token)
{
	t_astnode	*exec_node;
	t_astnode	*return_node;
	
	return_node = NULL;
	exec_node = NULL;
	while (token)
	{
		if (consume_redir(&return_node, &token))
			continue ;
		else if (!exec_node)
		{
			if (!is_token_exec(token->type))
			{
				printf("Unexpected token: %s; Expected: %s\n", decode(token->type), decode(EXEC));
				return (NULL);
			}
			exec_node = new_astnode(token);
			token = token->next;
		}
		else if (consume_exec_args(exec_node, &token))
			continue ;
		else
			break ;
	}
	if (!return_node)
		return (exec_node);
	add_child(return_node, exec_node);
	return (return_node);
}

bool	consume_redir(t_astnode **parent, t_token **token)
{
	static t_token_type	expected[] = {REDIR_OUT, REDIR_OUT_A, REDIR_IN};
	int					size;
	t_astnode			*temp;

	size = sizeof(expected) / sizeof(expected[0]);
	if (!match(*token, expected, size))
		return (0);
	temp = new_astnode(*token);
	*token = (*token)->next;
	(*token)->type = PATH;
	add_child(temp, new_astnode(*token));
	*token = (*token)->next;
	if (*parent)
		add_child(temp, *parent);
	*parent = temp;
	return (1);
}

bool	consume_exec_args(t_astnode *parent, t_token **token)
{
	static t_token_type	expected[] = {WORD, EXPAND_VAR, EXIT_STATUS};
	int					size;
	bool				ret;

	ret = 0;
	size = sizeof(expected) / sizeof(expected[0]);
	while (size-- > 0 && *token)
	{
		if (match(*token, expected, size + 1))
		{
			add_child(parent, new_astnode(*token));
			ret = 1;
		}
		else
			break ;
		*token = (*token)->next;
	}
	return (ret);
}
