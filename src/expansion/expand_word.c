#include "expansion_private.h"
#include <stdlib.h>

char	**expand_word(t_astnode *head, t_data *data)
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
