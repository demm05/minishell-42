#include "./heredoc_private.h"
#include "../extra/extra.h"
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

static inline char	*hash_key(char *tmpdir, unsigned int key)
{
	static char			name[24] = "/.minishell        .tmp";
	static char			hex[] = "0123456789abcdef";
	int					i;
	unsigned int		hash;

	hash = ((key >> 16) ^ key) * 0x45d9f3b;
	hash = ((hash >> 16) ^ hash) * 0x45d9f3b;
	hash = (hash >> 16) ^ hash;
	name[23] = '\0';
	i = 11;
	while (i < 19)
	{
		name[i++] = hex[hash & 0xf];
		hash >>= 4;
	}
	return (ft_strjoin(tmpdir, name));
}

int	tmp_new(t_tmp *t, char **tmpfileloc)
{
	struct stat		b;
	int				fc;
	unsigned int	*key;

	if (!t || !tmpfileloc)
		return (-1);
	t->file_count++;
	fc = t->file_count;
	if (fc > t->arr_size)
	{
		t->files = realloc(t->files, sizeof(int *) * fc * 2);
		t->arr_size = fc * 2;
	}
	t->files[fc - 1] = fc;
	key = &t->files[fc - 1];
	while (1)
	{
		*tmpfileloc = hash_key(t->tmpdir, *key);
		if (stat(*tmpfileloc, &b) != 0)
			break ;
		free(*tmpfileloc);
		*key += 1;
	}
	return (open(*tmpfileloc, O_RDWR | O_CREAT, 0644));
}

void	tmp_del(t_tmp *t)
{
	char	*file;
	int		i;

	i = 0;
	while (i < t->file_count)
	{
		file = hash_key(t->tmpdir, t->files[i]);
		if (unlink(file))
			perror("unlink");
		free(file);
		i++;
	}
	t->file_count = 0;
}

t_tmp	*tmp_alloc(void)
{
	t_tmp	*t;

	t = ft_calloc(1, sizeof(t_tmp));
	if (!t)
		return (NULL);
	if (access(P_tmpdir, W_OK) == 0)
		t->tmpdir = ft_strdup(P_tmpdir);
	else
	{
		t->tmpdir = get_curent_dir();
		if (access(t->tmpdir, W_OK) != 0)
		{
			free(t->tmpdir);
			t->tmpdir = NULL;
		}
	}
	if (!t->tmpdir)
	{
		fprintf(stderr, "heredoc: failed to set location for tmpdir");
		free(t);
		return (NULL);
	}
	return (t);
}
