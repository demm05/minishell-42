/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelnyk <dmelnyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 18:24:03 by dmelnyk           #+#    #+#             */
/*   Updated: 2025/04/07 18:24:03 by dmelnyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion_private.h"

static void	expand_home(t_lexer *l);
void		lex_wildcard(t_lexer *l);
void		lex_word(t_lexer *l);
static int	private_env_tes(const char *s, t_lexer *l);

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
		else if (private_env_tes(l.input + l.position, &l))
			lex_env(&l, 1);
		else if (l.ch == '~')
			expand_home(&l);
		else
			lex_word(&l);
	}
	return (l.tokens);
}

static void	expand_home(t_lexer *l)
{
	char	*s;

	s = getenv("HOME");
	if (s)
		append_advance(l, ft_strdup(s), 1, WORD);
	else
		append_alloc(l, WORD, 1);
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
		{
			escape = 0;
			append_advance(l, ft_strndup(s, i - 1), i, WORD);
			s = l->input + l->position;
			i = 0;
		}
		else if (s[i] == '\\')
			escape = !escape;
		else if (s[i] == '\'' || s[i] == '"' || s[i] == '*' || \
				private_env_tes(s + i, l) || s[i] == '~')
			break ;
		i++;
	}
	if (i)
		append_alloc(l, WORD, i);
}

static int	private_env_tes(const char *s, t_lexer *l)
{
	if (!s || *s != '$')
		return (0);
	if (s[1] == '"' || s[1] == '\'')
	{
		read_char(l);
		return (1);
	}
	return (is_valid_envv(s));
}
