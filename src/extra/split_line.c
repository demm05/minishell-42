#include "extra_private.h"

char	*ft_findnwln(char *s)
{
	bool	squote;
	bool	dquote;

	if (!s)
		return (NULL);
	squote = 0;
	dquote = 0;
	while (*s)
	{
		if (*s == '"' && dquote && !squote)
			dquote = !dquote;
		else if (*s == '\'' && squote && !dquote)
			squote = !squote;
		else if (*s == '\n' && !squote && !dquote)
			return (s);
		s++;
	}
	return (NULL);
}

void	split_line(t_data *data)
{
	char	*c;

	if (!data->line)
		return;
	c = ft_findnwln(data->line);
	if (!c)
		return ;
	data->next_line = ft_strdup(c + 1);
	*c = 0;
}
