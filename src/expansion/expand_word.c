#include "expansion_private.h"
#include <stdio.h>

t_token **get_array(t_token *token, bool split_it);

char	**expand_word(t_astnode *head, t_data *data, bool split_it)
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
	arr = get_array(token, split_it);
	if (!arr)
	{
		perror("malloc\n");
		return (NULL);
	}
	//wildcard_it(arr);
	res = join_tokens(arr);
	free(arr);
	return (res);
}

t_token **get_array(t_token *token, bool split_it)
{
	t_token	**arr;

	if (split_it)
		return (split_tokens(token));
	arr = malloc(sizeof(t_token *) * 2);
	if (!arr)
		return (NULL);
	arr[0] = token;
	arr[1] = NULL;
	return (arr);
}
