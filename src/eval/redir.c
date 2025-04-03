/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelnyk <dmelnyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:40:17 by dmelnyk           #+#    #+#             */
/*   Updated: 2025/03/12 12:48:21 by dmelnyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./eval_private.h"
#include <fcntl.h>
#include <errno.h>
#include <string.h>

static inline int	get_fd(t_astnode *head, t_data *data);
static inline bool	do_redir(t_astnode *head, t_data *data, int target, int fd);


bool	handle_redir(t_astnode *head, t_data *data)
{
	int	target;
	int	fd;
	int	copy;
	int	status;

	if (!head || !data)
		return (0);
	if (head->childs == 0)
		return (1);
	if (head->type == REDIR_IN)
		target = STDIN_FILENO;
	else if (head->type == REDIR_OUT || head->type == REDIR_OUT_A)
		target = STDOUT_FILENO;
	else
		return (1);
	fd = get_fd(head, data);
	if (fd == -2)
		return (0);
	if (fd == -1)
		return (1);
	copy = dup(target);
	status = do_redir(head->children, data, target, fd);
	dup2(copy, target);
	close(copy);
	return (status);
}

static inline bool	do_redir(t_astnode *head, t_data *data, int target, int fd)
{
	t_astnode	*to_eval;

	while (head && head->type == PATH)
		head = head->next;
	to_eval = head;
	dup2(fd, target);
	close(fd);
	if (to_eval)
		return (eval(to_eval, data));
	return (0);
}

static inline int	set_flags(t_token_type type)
{
	if (type == REDIR_OUT_A)
		return (O_WRONLY | O_CREAT | O_APPEND);
	if (type == REDIR_OUT)
		return (O_WRONLY | O_CREAT | O_TRUNC);
	if (type == REDIR_IN)
		return (O_RDONLY);
	return (0);
}

static inline int	get_fd(t_astnode *head, t_data *data)
{
	int			fd;
	t_astnode	*cur;

	cur = head->children;
	while (cur && cur->type != PATH)
		cur = cur->next;
	if (!cur)
		return (-1);
	if (!cur->literal)
		return (-2);
	fd = open(cur->literal, set_flags(head->type), 0644);
	if (fd == -1)
	{
		fprintf(stderr, "%s: %s\n", cur->literal, strerror(errno));
		data->exit_status = 1;
	}
	return (fd);
}
