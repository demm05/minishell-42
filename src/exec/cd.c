#include "../../inc/exec.h"
#include <limits.h>

int	m = 0;

char	*temp_strdup(t_astnode *head)
{
	char	*r;

	if (!head)
		return (NULL);
	if (!head->lit_size)
		return (NULL);
	r = malloc(sizeof(char) * (head->lit_size + 1));
	if (!r)
		return (NULL);
	strncpy(r, head->literal, head->lit_size);
	r[head->lit_size] = 0;
	m = 1;
	return (r);
}

// TODO: add proper error handle
bool	handle_cd(t_astnode *head, t_data *data)
{
	static char	last_dir[PATH_MAX];
	char		cur_dir[PATH_MAX];
	char		*path;
	char		save;

	save = 0;
	if (head->childs > 1)
	{
		printf("cd: too many arguments\n");
		data->exit_status = 1;
		return (1);
	}
	if (head->childs == 0)
		path = getenv("HOME");
	else
	{
		if (!getcwd(cur_dir, sizeof(cur_dir)))
			*cur_dir = '\0';
		if (*last_dir && *head->children->literal && *head->children->literal == '-')
			path = last_dir;
		else
			path = temp_strdup(head->children);
	}
	if (chdir(path))
	{
		printf("cd: : No such file or directory\n");
		data->exit_status = 1;
		if (m)
		{
			free(path);
			m = 0;
		}
		return (1);
	}
	strcpy(last_dir, cur_dir);
	if (m)
	{
		free(path);
		m = 0;
	}
	return (0);
}
