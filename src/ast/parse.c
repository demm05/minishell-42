/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelnyk <dmelnyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:02:15 by dmelnyk           #+#    #+#             */
/*   Updated: 2025/03/12 12:34:14 by dmelnyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ast_private.h"
#include <stdlib.h>

t_astnode	*parse(t_lexer *l)
{
	t_token		*t_head;
	t_astnode	*head;
	int			status;

	if (!l || !l->tokens || l->tokens->type == EOL)
		return (NULL);
	status = analyze_tokens(l);
	if (status)
		return (NULL);
	t_head = l->tokens;
	head = parse_logical_exp(&t_head);
	if (!head)
		return (NULL);
	return (head);
}

t_astnode	*parse_logical_exp(t_token **token)
{
	static t_token_type	exp[] = {AND, OR};
	t_astnode			*left;	
	t_astnode			*head;

	left = parse_pipe(token);
	if (left && match(*token, exp, 2))
	{
		head = new_astnode(*token);
		*token = (*token)->next;
		add_child(head, left);
		add_child(head, parse_logical_exp(token));
		return (head);
	}
	return (left);
}

t_astnode	*parse_pipe(t_token **token)
{
	t_astnode	*left;	
	t_astnode	*head;

	left = parse_redir(token);
	if (left && *token && (*token)->type == PIPE)
	{
		head = new_astnode(*token);
		*token = (*token)->next;
		add_child(head, left);
		add_child(head, parse_pipe(token));
		return (head);
	}
	return (left);
}
