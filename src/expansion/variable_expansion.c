#include "expansion_private.h"
#include "../extra/extra.h"
#include <stdio.h>

static inline int	count_words(const char *s, int *size)
{
	const char	*anch;
	int			word_count;
	bool		state;

	*size = 0;
	if (!s)
		return (0);
	anch = s;
	word_count = 0;
	state = 0;
	while (*s)
	{
		if (ft_isspace((unsigned char)*s))
			state = 0;
		else if (!state)
		{
			state = 1;
			word_count++;
		}
		s++;
	}
	*size = s - anch;
	if (*size > 0)
		*size -= 1;
	return (word_count);
}

static inline char	*get_key(t_data *data, char *key)
{
	t_env	*env;

	if (!data || !key)
		return (NULL);
	env = getenv_val(data->env, key);
	free(key);
	if (!env)
		return (NULL);
	return (env->value);
}

static inline void	split_it(char *s, char **res)
{
	int		i;
	int		j;

	if (!s)
		return ;
	i = 0;
	while (*s)
	{
		j = 0;
		while (*s && ft_isspace(*s))
			s++;
		while (s[j] && !ft_isspace(s[j]))
			j++;
		if (j > 0)
			res[i++] = ft_strndup(s, j);
		s += j;
	}
	res[i] = NULL;
}

static inline void	add_tokens_to_the_list(t_lexer *l, char *key,
										char **s, int size)
{
	int	i;

	if (l->tokens && ft_isspace(*key))
		append_advance(l, NULL, 0, SSPACE);
	i = 0;
	while (s[i])
	{
		append_advance(l, s[i], 0, WORD);
		if (s[++i])
			append_advance(l, NULL, 0, SSPACE);
	}
	if (size > 0 && ft_isspace(key[size]))
		append_advance(l, NULL, 0, SSPACE);
	free(s);
}

void	expand_variable(t_lexer *l, char *key, bool is_status, int size)
{
	char	**res;

	if (is_status)
	{
		append_advance(l, ft_itoa(l->data->exit_status), size, WORD);
		return ;
	}
	l->read_postion += size - 1;
	read_char(l);
	key = get_key(l->data, key);
	if (!key)
	{
		append_advance(l, NULL, 0, WORD);
		return ;
	}
	res = ft_calloc(count_words(key, &size) + 1, sizeof(char *));
	if (!res)
	{
		perror("malloc\n");
		free(key);
		return ;
	}
	split_it(key, res);
	add_tokens_to_the_list(l, key, res, size);
}
