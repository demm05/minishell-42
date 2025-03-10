#include "../inc/minishell.h"

int	main(void)
{
	char	*s;

	s = mini_read("Prompt > ");
	if (s)
		printf("%d\n", strlen(s));
	else
		printf("%s\n", NULL);
	free(s);
	return (0);
}
