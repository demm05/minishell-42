#include "expansion_private.h"
#include <stdio.h>
#include <stdlib.h>

static inline char	**expand_path(t_astnode *head, t_data *data)
{
	t_token	*token;
	t_token	**arr;
	char	**res;

	if (!head || !head->literal)
		return (NULL);
	token = word_generate_tokens(head->literal, data);
	if (!token)
		return (NULL);
	arr = ft_calloc(2, sizeof(t_token *));
	arr[0] = token;
	//wildcard_it(arr);
	res = join_tokens(arr);
	free(arr);
	return (res);
}

void	do_path(t_astnode *head, t_data *data)
{
	char		**s;
	int			i;

	s = expand_path(head, data);
	if (!s)
		return ;
	if (s[1])
	{
		fprintf(stderr, "%s: ambiguous redirect\n", head->literal);
		i = 0;
		while (s[i])
			free(s[i++]);
		free(s);
		return ;
	}
	free(head->literal);
	head->literal = *s;
	free(s);
}
