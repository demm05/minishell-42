/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelnyk <dmelnyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 10:37:10 by dmelnyk           #+#    #+#             */
/*   Updated: 2025/03/22 11:22:24 by dmelnyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tok_private.h"

bool	is_fixed_type(t_lexer *l);

t_token	*generate_tokens(char *line)
{
	t_lexer	l;

	ft_bzero(&l, sizeof(t_lexer));
	l.input = line;
	l.size = ft_strlen(line);
	read_char(&l);
	while (l.position < l.size)
	{
		if (l.tokens && l.tokens->prev->type == ILLEGAL)
			return (l.tokens);
		if (!(l.ch == '\n' && l.tokens && l.tokens->prev->type != SEQUENCE))
			eat_whitespaces(&l);
		if (is_fixed_type(&l))
			continue ;
		else if (l.ch)
			add_word(&l);
		else
			break ;
	}
	append_advance(&l, NULL, 0, EOL);
	return (l.tokens);
}

bool	is_fixed_type(t_lexer *l)
{
	if (l->ch == '|' && peek_char(l) == '|')
		append_advance(l, NULL, 2, OR);
	else if (l->ch == '|')
		append_advance(l, NULL, 1, PIPE);
	else if (l->ch == '&' && peek_char(l) == '&')
		append_advance(l, NULL, 2, AND);
	else if (l->ch == '&')
		append_advance(l, NULL, 2, ILLEGAL);
	else if (l->ch == '>' && peek_char(l) == '>')
		append_advance(l, NULL, 2, REDIR_OUT_A);
	else if (l->ch == '>')
		append_advance(l, NULL, 1, REDIR_OUT);
	else if (l->ch == '<' && peek_char(l) == '<')
		append_advance(l, NULL, 2, HERE_DOC);
	else if (l->ch == '<')
		append_advance(l, NULL, 1, REDIR_IN);
	else if (l->ch == '(')
		append_advance(l, NULL, 1, LPAREN);
	else if (l->ch == ')')
		append_advance(l, NULL, 1, RPAREN);
	else if (l->ch == ';' || l->ch == '\n')
		append_advance(l, NULL, 1, SEQUENCE);
	else
		return (0);
	return (1);
}
