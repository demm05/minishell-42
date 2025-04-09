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
#include <fcntl.h>

static bool	is_paran(t_token **head, int *paren);
static bool	is_basic(t_token *head);
static bool	a_is_redir(t_token **head);

static inline bool	aheredoc(t_data *data, t_token **head)
{
	char	*filename;

	(*head)->type = REDIR_IN;
	*head = (*head)->next;
	if ((*head)->type != WORD)
		return (1);
	filename = heredoc(data, (*head)->literal);
	free((*head)->literal);
	(*head)->literal = filename;
	return (0);
}

bool	analyze_tokens(t_data *data, t_token *head)
{
	int		paren;

	paren = 0;
	while (head)
	{
		if (head->type == ILLEGAL)
		{
			ft_fprintf(STDERR_FILENO, "syntax error: unexpected end of file\n");
			return (1);
		}
		else if (head->type == HERE_DOC && aheredoc(data, &head))
			break ;
		else if (is_basic(head) || is_paran(&head, &paren) || a_is_redir(&head))
			break ;
		head = head->next;
	}
	if (head)
		ft_fprintf(STDERR_FILENO, "syntax error near unexpected token %s\n",
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
	if (head->next->type == SEQUENCE)
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
		if (prev && prev->type != OR && prev->type != AND && prev->type != PIPE
			&& prev->type != LPAREN)
			return (1);
		*paren += 1;
	}
	else if ((*head)->type == RPAREN)
	{
		if ((prev && prev->type == LPAREN) || *paren < 1)
			return (1);
		*paren -= 1;
	}
	return (0);
}
