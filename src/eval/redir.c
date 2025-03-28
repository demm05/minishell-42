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
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

static int			get_fd(char *file, t_token_type type);
static t_astnode	*do_redir(t_astnode *parent, int target, t_token_type type);

bool	handle_redir(t_astnode *head, t_data *data)
{
	t_astnode	*exec;
	int			target;
	int			copy;

	if (!head || !data)
		return (0);
	if (head->childs < 1)
		return (1);
	if (head->type == REDIR_IN)
		target = STDIN_FILENO;
	else if (head->type == REDIR_OUT || head->type == REDIR_OUT_A)
		target = STDOUT_FILENO;
	else
		return (1);
	copy = dup(target);
	exec = do_redir(head->children, target, head->type);
	if (exec)
		eval(exec, data);
	dup2(copy, target);
	close(copy);
	return (exec == NULL);
}

static inline t_astnode	*do_redir(t_astnode *head, int target,
								t_token_type type)
{
	t_astnode	*ptr;
	t_astnode	*res;
	t_astnode	*path;
	int			fd;

	ptr = head;
	while (head && head->type != PATH)
		head = head->next;
	path = head;
	head = ptr;
	while (head && head->type == PATH)
		head = head->next;
	res = head;
	if (path)
	{
		fd = get_fd(path->literal, type);
		if (fd == -1)
			return (NULL);
		dup2(fd, target);
		close(fd);
	}
	return (res);
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

static inline int	get_fd(char	*file, t_token_type type)
{
	int			fd;

	if (!file)
		return (-1);
	fd = open(file, set_flags(type), 0644);
	if (fd == -1)
		perror(file);
	return (fd);
}
