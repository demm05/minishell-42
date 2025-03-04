#include "../../inc/exec.h"

bool	handle_pwd(t_astnode *head, t_data *data)
{
	char	cwd[1024];
	getcwd(cwd, sizeof(cwd));
	printf("%s\n", cwd);
	return (0);
}
