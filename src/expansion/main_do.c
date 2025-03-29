#include "expansion_private.h"

static inline char	**expand_word(t_astnode *head, t_data *data)
{
	t_token	*token;
	t_token	**arr;
	char	**res;

	if (!head || !head->literal)
		return (NULL);
	token = word_generate_tokens(head->literal, data);
	if (!token)
		return (NULL);
	//print_tokens(token);
	arr = split_tokens(token);
	//wildcard_it(arr);
	res = join_tokens(arr);
	free(arr);
	return (res);
}


static inline void	set_type(t_astnode *head)
{
	char			*s;

	s = head->literal;
	if (ft_strcmp(s, "echo") == 0)
		head->type = ECHO;
	else if (ft_strcmp(s, "pwd") == 0)
		head->type = PWD;
	else if (ft_strcmp(s, "cd") == 0)
		head->type = CD;
	else if (ft_strcmp(s, "export") == 0)
		head->type = EXPORT;
	else if (ft_strcmp(s, "env") == 0)
		head->type = ENV;
	else if (ft_strcmp(s, "unset") == 0)
		head->type = UNSET;
	else if (ft_strcmp(s, "exit") == 0)
		head->type = EXIT;
}

static inline t_astnode	*create_nodes(char **ss)
{
	t_astnode	*res;
	t_token		t;
	int			i;

	if (!ss || !*ss)
		return (NULL);
	i = 0;
	t.type = WORD;
	res = NULL;
	while (ss[i])
	{
		t.literal = ss[i];
		t.size = ft_strlen(ss[i]);
		append_astnode(&res, new_astnode(&t));
		i++;
	}
	return (res);
}

void	do_child(t_astnode *head, t_astnode *cur, t_data *data)
{
	t_astnode	*new;
	t_astnode	*next;
	t_astnode	*new_last;
	char		**s;

	s = expand_word(cur, data);
	if (!s)
		return ;
	free(cur->literal);
	cur->literal = *s;
	new = create_nodes(s + 1);
	free(s);
	if (!new)
		return ;
	next = cur->next;
	new_last = new->prev;
	if (!head->next)
		head->prev = new_last;
	else if (next)
		next->prev = new_last;
	new_last->next = next;	
	cur->next = new;
	new->prev = cur;
}

void	do_head(t_astnode *head, t_data *data)
{
	t_astnode	*new;
	t_astnode	*old_last;
	char		**s;

	s = expand_word(head, data);
	if (!s)
		return ;
	free(head->literal);
	head->literal = *s;
	set_type(head);	
	new = create_nodes(s + 1);
	free(s);
	if (!new)
		return ;
	if (!head->children)
	{
		head->children = new;
		return ;
	}
	new->prev->next = head->children;
	old_last = head->children->prev;
	head->children = new;
	head->children->prev = old_last;
}

