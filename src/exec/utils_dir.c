#include "../../inc/exec.h"
#include <limits.h>

char	*get_curent_dir(void)
{
	return (getcwd(NULL, 0));
}
