/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelnyk <dmelnyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 18:24:09 by dmelnyk           #+#    #+#             */
/*   Updated: 2025/04/07 18:24:09 by dmelnyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion_private.h"
#include <stdio.h>

void	split_env_add_token(t_lexer *l, char *key, char *value);
static void	add_tokens_to_the_list(t_lexer *l, char *key, char **s, int size);

bool	is_valid_envv(const char *s)
{
	if (!s || s[0] != '$')
		return (0);
	if (!ft_isalpha(s[1]) && s[1] != '_' && s[1] != '?')
		return (0);
	return (1);
}

void	lex_env(t_lexer *l, bool to_split)
{
	char		*key;
	char		*value;

	if (!is_valid_envv(l->input + l->position))
		return ;
	if (peek_char(l) == '?')
	{
		append_advance(l, ft_itoa(l->data->exit_status), 2, EXIT_STATUS);
		return ;
	}
	key = env_get_key(l->input + l->position);
	value = env_get_value(l->data->env, key);
	if (!value)
		append_advance(l, NULL, ft_strlen(key) + 1, WORD);
	else if (!*value)
		append_advance(l, ft_strdup(""), ft_strlen(key) + 1, WORD);
	else if (!to_split)
		append_advance(l, ft_strdup(value), ft_strlen(key) + 1, WORD);
	else
		split_env_add_token(l, key, value);
	free(key);
}

void	split_env_add_token(t_lexer *l, char *key, char *value)
{
	char	**sp;
	int		size;

	if (!value || !key)
		return ;
	size = ft_strlen(key);
	l->read_postion += size;
	read_char(l);
	sp = ft_split(value, " \n\t\r\f");
	if (!sp)
		return ;
	add_tokens_to_the_list(l, value, sp, ft_strlen(value));
}

static void	add_tokens_to_the_list(t_lexer *l, char *value, char **s, int size)
{
	int	i;

	if (l->tokens && ft_isspace(*value))
		append_advance(l, NULL, 0, SSPACE);
	i = 0;
	while (s[i])
	{
		append_advance(l, s[i], 0, WORD);
		if (s[++i])
			append_advance(l, NULL, 0, SSPACE);
	}
	if (size > 0 && !(l->tokens && l->tokens->prev->type == SSPACE) &&  ft_isspace(value[size - 1]))
		append_advance(l, NULL, 0, SSPACE);
	free(s);
}
