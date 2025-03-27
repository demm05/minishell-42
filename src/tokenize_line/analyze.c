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
#include <stdio.h>
#include <readline/readline.h>

static bool	is_paran(t_token **head, int *paren);
static bool	is_basic(t_token *head);
static bool	a_is_redir(t_token **head);

int	read_heredoc(const char *delimiter)
{
	char	*line;
	int		pfd[2];

	if (pipe(pfd) < 0)
		fprintf(stderr, "pipe error\n");
	while (1)
	{
		line  = readline("> ");
		if (line == NULL)
			break ;
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		dprintf(pfd[1], "%s\n", line);
		free(line);
	}
	close(pfd[1]);
	return (pfd[0]);
}

bool	analyze_tokens(t_token *head)
{
	int	paren;

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
			head = head->next;
			if (head->type != WORD)
				break ;
			read_heredoc(head->literal);
			fprintf(stderr, "syntax error HEREDOC is not supported yet\n");
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
