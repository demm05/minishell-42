/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelnyk <dmelnyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 12:10:01 by dmelnyk           #+#    #+#             */
/*   Updated: 2025/03/22 14:34:13 by dmelnyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "const_word_private.h"
#include "../extra/extra.h"

static inline bool	is_valid_ch(char c)
{
	return (((c >= 'a' && c <= 'z') || \
			(c >= 'A' && c <= 'Z')) || \
			c == '_' || \
			(c >= '0' && c <= '9'));
}

void	lex_env(t_lexer *l)
{
	int			len;
	const char	*str;

	if (peek_char(l) == '?')
	{
		append_alloc(l, EXIT_STATUS, 2);
		return ;
	}
	read_char(l);
	len = 0;
	str = l->input + l->position;
	while (len < l->size && is_valid_ch(str[len]))
		len++;
	append_alloc(l, EXPAND_VAR, len);
}

void	expand_variables(t_token *tok, t_data *data)
{
	t_env	*env;

	while (tok)
	{
		if (tok->type == EXIT_STATUS || tok->type == EXPAND_VAR)
		{
			if (tok->type == EXPAND_VAR)
			{
				env = getenv_val(data->env, tok->literal);
				free(tok->literal);
				if (env)
					tok->literal = env->value;
				else
					tok->literal = NULL;
			}
			else
			{
				free(tok->literal);
				tok->literal = ft_itoa(data->exit_status);
			}
			tok->type = WORD;
			if (tok->literal)
				tok->size = ft_strlen(tok->literal);
			else
				tok->size = 0;
		}
		tok = tok->next;
	}
}

