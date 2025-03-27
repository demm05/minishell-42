/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelnyk <dmelnyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 11:38:28 by dmelnyk           #+#    #+#             */
/*   Updated: 2025/03/22 14:32:17 by dmelnyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "const_word_private.h"

bool	is_valid_envv(const char *s)
{
	if (!s || s[0] != '$')
		return (0);
	if (!ft_isalpha(s[1]) && s[1] != '_' && s[1] != '?')
		return (0);
	return (1);
}

t_token	*word_generate_tokens(char *line, t_data *data)
{
	t_lexer	l;

	ft_bzero(&l, sizeof(t_lexer));
	l.input = line;
	l.size = ft_strlen(line);
	l.data = data;
	read_char(&l);
	while (l.position < l.size)
	{
		if (l.ch == '\'' || l.ch == '"')
			lex_quote(&l);
		else if (l.ch == '*')
			lex_wildcard(&l);
		else if (is_valid_envv(l.input + l.position))
			lex_env(&l);
		else
			lex_word(&l);
	}
	return (l.tokens);
}

void	lex_wildcard(t_lexer *l)
{
	const char	*s;
	int			i;

	if (l->ch != '*')
		return ;
	i = 0;
	s = l->input + l->position;
	while (s[i] == '*')
		i++;
	append_alloc(l, WILDCARD, i);
}

void	lex_word(t_lexer *l)
{
	const char	*s;
	int			i;
	bool		escape;

	i = 0;
	escape = 0;
	s = l->input + l->position;
	while (s[i])
	{
		if (escape)
			escape = 0;
		else if (s[i] == '\\')
			escape = !escape;
		else if (s[i] == '\'' || s[i] == '"' || s[i] == '*' || \
			is_valid_envv(s + i)) 
			break ;
		i++;
	}
	append_alloc(l, WORD, i);
}
