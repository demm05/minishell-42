/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expression.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelnyk <dmelnyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:01:09 by dmelnyk           #+#    #+#             */
/*   Updated: 2025/04/07 18:23:07 by dmelnyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ast_private.h"

t_astnode	*parse_sequence(t_token **token)
{
	t_astnode	*head;

	head = parse_logical_exp(token);
	if (head && *token && (*token)->type == SEQUENCE)
	{
		*token = (*token)->next;
		if (!(*token) || (*token)->type == EOL)
			return (head);
		head->next = parse_sequence(token);
	}
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

	left = parse_paren(token);
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

t_astnode	*parse_paren(t_token **token)
{
	t_astnode	*head;
	t_astnode	*result;

	if (*token && (*token)->type == LPAREN)
	{
		*token = (*token)->next;
		head = parse_sequence(token);
		if (*token && (*token)->type == RPAREN)
		{
			*token = (*token)->next;
			result = parse_redir_only(token, head);
			if (result)
				return (result);
			return (head);
		}
		else
		{
			ft_fprintf(STDERR_FILENO, "Unexpected error\n");
			free_ast(&head);
			exit(127);
		}
	}
	return (parse_redir(token));
}
