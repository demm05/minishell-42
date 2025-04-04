#include "../src/construct_word/const_word_private.h"
#include "../src/extra/extra.h"
#include <stdio.h>

static inline void	expand_variable(t_token *tok, t_data *data);
static inline int	get_size(t_token *head, t_data *data);
static inline t_token	*set_head(t_token *head);

static inline void	add_tok_to_arr(t_token *head, t_token *new, t_token **res, int *index)
{
	new->next = head->next;
	head->next = NULL;
	res[*index] = new;
	*index += 1;
	if (new->next)
		new->next->prev = new;
}

t_token	**process_tokens(t_token *head, t_data *data)
{
	t_token	**res;
	t_token	*next;
	t_token	*new;
	int		size;
	int		i;
	bool	quote;

	size = get_size(head, data);
	res = malloc(sizeof(t_token *) * (size + 1));
	i = 0;
	quote = 0;
	if (!res)
	{
		perror("malloc\n");
		return (NULL);
	}
	if (head)
		res[i++] = head;
	while (head)
	{
		next = head->next;
		if (head->type == QUOTE)
			quote = !quote;
		else if (!quote)
		{
			new = set_head(head);
			if (new)
			{
				add_tok_to_arr(head, new, res, &i);
				head = new;
				continue ;
			}
		}
		head = next;
	}
	res[i] = NULL;
	return (res);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;
	t_token	*t;
	t_token	**arr;
	
	data = init(argc, argv, envp);
	t = word_generate_tokens("$A$A");
	if (!t)
		return (0);
	arr = process_tokens(t, data);
	int	i = 0;
	while (arr[i])
		print_tokens(arr[i++]);
	printf("%d\n", i);
}

static inline t_token	*set_head(t_token *head)
{
	int		start;
	int		end;
	int		reminder_start;
	char	*first;
	t_token	*new;

	if (!head || !head->literal)
		return (NULL);
	start = 0;
	end = 0;
	new = NULL;
	while (start < head->size && ft_isspace(head->literal[start]))
		start++;
	if (start == head->size)
	{
		free(head->literal);
		head->literal = NULL;
		head->size = 0;
		return (NULL);
	}
	end = start;
	while (end < head->size && !ft_isspace(head->literal[end]))
		end++;
	if (end - start == head->size)
		return (NULL);
	reminder_start = end;
	while (reminder_start < head->size && ft_isspace(head->literal[reminder_start]))
		reminder_start++;
	first = ft_strndup(head->literal + start, end - start);
	if (reminder_start < head->size)
	{
		new = new_token(WORD, ft_strdup(head->literal + reminder_start), head->size - reminder_start);
		new->size = head->size - reminder_start;
	}
	free(head->literal);
	head->literal = first;
	head->size = end - start;
	return (new);
}

static inline int	get_size(t_token *head, t_data *data)
{
	int		i;
	int		j;
	bool	quote;

	i = 1;
	quote = 0;
	while (head)
	{
		if (head->type == QUOTE)
			quote = !quote;
		else if (head->type == EXIT_STATUS || head->type == EXPAND_VAR)
		{
			j = 0;
			expand_variable(head, data);
			if (!quote)
			{
				while (j < head->size)
					if (ft_isspace(head->literal[j++]))
						i++;
			}

		}
		head = head->next;
	}
	return (i);
}

static inline void	expand_variable(t_token *tok, t_data *data)
{
	t_env	*env;

	if (tok->type == EXPAND_VAR)
	{
		env = getenv_val(data->env, tok->literal);
		free(tok->literal);
		if (env)
			tok->literal = ft_strdup(env->value);
		else
			tok->literal = NULL;
	}
	else if (tok->type == EXIT_STATUS)
	{
		free(tok->literal);
		tok->literal = ft_itoa(data->exit_status);
	}
	else
		return ;
	tok->type = WORD;
	tok->size = ft_strlen(tok->literal);
}
