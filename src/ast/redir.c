/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelnyk <dmelnyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 11:17:49 by dmelnyk           #+#    #+#             */
/*   Updated: 2025/03/21 17:39:32 by dmelnyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ast_private.h"
#include <stdlib.h>
#include <stdio.h>

static t_astnode	*new_redirection(t_token **token, t_astnode *head);

t_astnode	*parse_redir(t_token **token)
{
	static t_token_type	exp[] = {REDIR_OUT, REDIR_OUT_A, REDIR_IN, HERE_DOC};
	static t_token_type	end[] = {AND, OR, PIPE, RPAREN};
	t_astnode			*left;	
	t_astnode			*head;
	t_astnode			*last_head;

	left = parse_exec(*token);
	head = NULL;
	last_head = NULL;
	while (*token)
	{
		while (*token && !match(*token, exp, 4) && !match(*token, end, 4))
			*token = (*token)->next;
		if (!match(*token, exp, 4))
			break ;
		last_head = new_redirection(token, last_head);
		if (!head)
			head = last_head;
	}
	if (!head)
		return (left);
	if (left)
		add_child(last_head, left);
	return (head);
}

static t_astnode	*new_redirection(t_token **token, t_astnode *head)
{
	t_astnode	*new;
	t_astnode	*path;

	new = new_astnode(*token);
	*token = (*token)->next;
	if (!*token)
	{
		fprintf(stderr, "THERE SHOULDN'T be syntax erro\n");
		exit(127);
	}
	path = new_astnode(*token);
	*token = (*token)->next;
	path->type = PATH;
	add_child(new, path);
	if (head)
		add_child(head, new);
	return (new);
}
