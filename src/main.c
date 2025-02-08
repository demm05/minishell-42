# include "../inc/minishell.h"

int	main(int argc, char **argv)
{
	char	*line;

	line = readline("Promt > ");
	free(line);
	return (0);
}
