#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

typedef struct	s_state
{
	int		**wildcards;
	bool	dquote;
	bool	squote;
	bool	escape;
}	t_state;

// TODO: First we should expand all enviroment variables
// TODO: Then we should save location of wildcards
// TODO: Then we should remove quotes
// TODO: Then we if there is wildcards we should wildcard it
// TODO: Now we've got complete string

char	*expand_vars(char *s)
{
	char	*anch;
	int		len;
	t_state	st;

	if (!s)
		return (NULL);
	bzero(&st, sizeof(t_state));
	anch = s;
	while (*s)
	{
		if (*s == '"' && !st.squote)
			st.dquote = !st.dquote;
		else if (*s == '\'' && !st.dquote)
			st.squote= !st.squote;
		len++;
	}
}

int	main(void)
{
	char *s = "$SHELL";
	int	len;
	char *res;
}
