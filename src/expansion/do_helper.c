#include "expansion_private.h"
#include <stdlib.h>

t_astnode	*create_nodes(char **ss)
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
