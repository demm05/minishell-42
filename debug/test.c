#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <strings.h>
#include <ctype.h>

typedef struct	s_state
{
	bool	dquote;
	bool	squote;
	bool	escape;
}	t_state;

// TODO: First we should expand all enviroment variables
// TODO: Then we should save location of wildcards
// TODO: Then we should remove quotes
// TODO: Then we if there is wildcards we should wildcard it
// TODO: Now we've got complete string

int	main(void)
{
	char *s = "$SHELL";
	int	len;
	char *res;
}
