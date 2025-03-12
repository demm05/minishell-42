/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_quote.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelnyk <dmelnyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:26:08 by dmelnyk           #+#    #+#             */
/*   Updated: 2025/03/12 12:26:09 by dmelnyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./lexer_private.h"

static void	read_squote(t_lexer *l)
{
	int	pos;

	pos = l->position;
	while (pos < l->size && l->input[pos] != '\'')
		pos++;

	if (l->input[pos] == '\'')
	{
		append_alloc(l, WORD, pos - l->position);
		read_char(l);
	}
	else
		append_alloc(l, ILLEGAL, pos - --l->position);
}

static void	read_dquote(t_lexer *l)
{
	int	pos;

	pos = l->position;
	while (pos < l->size)
	{
		if (l->ch == '\\')
		{
			append_alloc(l, WORD, pos - l->position - 1);
			read_char(l);
			pos = l->position;
		}
		else if (l->input[pos] == '"')
			break ;
		else if (l->input[pos] == '$')
		{
			append_alloc(l, WORD, pos - l->position);
			lex_env_var(l);
			pos = l->position;
		}
		else
			pos++;
	}
	if (l->input[pos] == '"')
	{
		if (pos > l->position)
			append_alloc(l, WORD, pos - l->position);
		read_char(l);
	}
	else
		append_alloc(l, ILLEGAL, pos - --l->position);
}

int	lex_quote(t_lexer *l)
{
	if (l->ch != '\'' && l->ch != '"')
		return (0);
	// TODO: add token as quote so exec could enter heredoc when quote is missing
	if (l->ch == '\'')
	{
		read_char(l);
		if (l->ch == '\'')
			read_char(l);
		else
			read_squote(l);
	}
	else if (l->ch == '"')
	{
		read_char(l);
		if (l->ch == '"')
			read_char(l);
		else
			read_dquote(l);
	}
	return (1);
}
