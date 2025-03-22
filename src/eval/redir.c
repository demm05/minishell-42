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

static int	get_fd(t_astnode *head, t_data *data);

bool handle_redir(t_astnode *head, t_data *data)
{
    t_astnode	*cur;
    int			 fd;
    int			 copy_fd;
    int			 target_fd;

    if (!head || !data)
        return (0);
        
    if (head->type == REDIR_IN)
        target_fd = STDIN_FILENO;
    else if (head->type == REDIR_OUT || head->type == REDIR_OUT_A)
        target_fd = STDOUT_FILENO;
    else
    {
		fprintf(stderr, "heredoc currently is unsuported\n");
    	return (1);
    }

    fd = get_fd(head, data);
    if (fd == -1)
        return (1);
    // Save the original file descriptor
    copy_fd = dup(target_fd);
    
    // Redirect the appropriate standard file descriptor
    dup2(fd, target_fd);
    close(fd);
    
    // Find the command to execute
    cur = head->children;
    while (cur && !is_token_exec(cur->type))
        cur = cur->next;
        
    if (!cur)
    {
    	dup2(copy_fd, target_fd);
    	close(copy_fd);
        return (1);
    }
        
    // Execute the command with redirection in place
    eval(cur, data);
    
    // Restore the original file descriptor
    dup2(copy_fd, target_fd);
    close(copy_fd);
    
    return (0);
}

static int	set_flags(t_token_type type)
{
	if (type == REDIR_OUT_A)
		return (O_WRONLY | O_CREAT | O_APPEND);
	if (type == REDIR_OUT)
		return (O_WRONLY | O_CREAT | O_TRUNC);
	if (type == REDIR_IN)
		return (O_RDONLY);
	return (0);
}

static int	get_fd(t_astnode *parent, t_data *data)
{
	t_astnode	*head;
	int			fd;

	head = parent->children;
	while (head)
	{
		if (is_redir(head->type))
			handle_redir(head, data);
		else if (!is_token_exec(head->type))
			break ;
		head = head->next;
	}
	if (!head)
		return (-1);
	fd = open(head->literal, set_flags(parent->type), 0644);
	if (fd == -1)
		perror(head->literal);
	return (fd);
}
