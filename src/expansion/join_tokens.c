#include "expansion_private.h"

static inline unsigned int	get_list_size(t_token *head)
{
	unsigned int	len;

	len = 0;
	while (head)
	{
		len += head->size;
		head = head->next;
	}
	return (len);
}

static inline char	*join_head(t_token *head)
{
	char			*res;
	unsigned int	size;
	int				j;
	int				k;

	j = 0;
	size = get_list_size(head);
	res = malloc(sizeof(char) *(size + 1));
	if (!res)
	{
		perror("malloc");
		return (NULL);
	}
	while (head)
	{
		k = 0;
		while (k < head->size)
			res[j++] = head->literal[k++];
		free(head->literal);
		head = head->next;
	}
	res[j] = 0;
	return (res);
}

static inline int	get_arr_size(t_token **head)
{
	int		size;

	if (!head || !*head)
		return (0);
	size = 0;
	while (head[size])
		size++;
	return (size);
}

char	**join_tokens(t_token **head)
{
	char	**res;
	char	*s;
	int		i;

	if (!head || !*head)
		return (NULL);
	res = malloc(sizeof(char *) * (get_arr_size(head) + 1));
	if (!res)
	{
		perror("malloc");
		return (NULL);
	}
	i = 0;
	while (head[i])
	{
		s = join_head(head[i]);
		free_tokens(&head[i], 0);
		res[i++] = s;
	}
	res[i] = NULL;
	return (res);
}
