/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyze.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelnyk <dmelnyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 11:24:08 by dmelnyk           #+#    #+#             */
/*   Updated: 2025/03/22 11:22:48 by dmelnyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tok_private.h"
#include "../heredoc/heredoc.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

static bool	is_paran(t_token **head, int *paren);
static bool	is_basic(t_token *head);
static bool	a_is_redir(t_token **head);

bool	analyze_tokens(t_token *head)
{
	int		paren;
	char	*heredoc_file;

	paren = 0;
	while (head)
	{
		if (head->type == ILLEGAL)
		{
			fprintf(stderr, "syntax error: unexpected end of file\n");
			return (1);
		}
		else if (head->type == HERE_DOC)
		{
			head->type = REDIR_IN;
			head = head->next;
			if (head->type != WORD)
				break ;
			heredoc_file = read_heredoc(head);
			if (!heredoc_file)
			{
				fprintf(stderr, "failed to process heredoc\n");
				return (true);
			}
			free(head->literal);
			head->literal = heredoc_file;
		}
		else if (is_basic(head) || is_paran(&head, &paren) || a_is_redir(&head))
			break ;
		head = head->next;
	}
	if (head)
		fprintf(stderr, "syntax error near unexpected token %s\n",
			decode(head->type));
	return (head != NULL);
}

static bool	is_basic(t_token *head)
{
	if (!(head->type == AND || head->type == OR || head->type == PIPE))
		return (0);
	if (head->type == AND || head->type == OR || head->type == PIPE)
		return (1);
	if (!head->prev->next)
		return (1);
	if (!head->next || !head->next->next)
		return (1);
	return (0);
}

static bool	a_is_redir(t_token **head)
{
	if (!head || !*head)
		return (0);
	if (!is_redir((*head)->type))
		return (0);
	*head = (*head)->next;
	if (!*head || (*head)->type != WORD)
		return (1);
	return (0);
}

static bool	is_paran(t_token **head, int *paren)
{
	t_token		*prev;

	prev = NULL;
	if ((*head)->prev->next)
		prev = (*head)->prev;
	if ((*head)->type == LPAREN)
	{
		if (prev && prev->type != OR && prev->type != AND && prev->type != PIPE)
			return (1);
		*paren += 1;
	}
	else if ((*head)->type == RPAREN)
	{
		if ((prev && prev->type == LPAREN) || *paren < 1)
			return (1);
		*paren += 1;
	}
	return (0);
}
