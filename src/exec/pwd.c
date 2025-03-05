#include "../../inc/exec.h"

bool	handle_pwd(t_astnode *head, t_data *data)
{
	char	*buf;

	buf = get_curent_dir();
	if (!buf)
		return (1);
	puts(buf);
	free(buf);
	return (0);
}
