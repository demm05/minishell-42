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
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <readline/readline.h>

static bool	is_paran(t_token **head, int *paren);
static bool	is_basic(t_token *head);
static bool	a_is_redir(t_token **head);

//TODO:
//write to the temp file
//cannot use pipe. use temp file instead.
//If reached EOL or find delimiter then, 
//TODO: This function return the name of the temp file?
//and output using the file with other function?
const char	*read_heredoc(const char *delimiter)
{
	char	*line;
	int		fd;
	const char *filename = "heredoc_tmp.txt";
	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd < 0)
	{
		perror("open");
		return (NULL);
	}
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
	return (filename);

	//TODO: delete this and modify for handling the redirection process.
	//fd = open(filename, O_RDONLY);
	//if (fd < 0)
	//{
	//	perror("open for reading");
	//	return ;
	//}
	//char buffer[1024];
	//ssize_t bytes;
	//while ((bytes = read(fd, buffer, sizeof(buffer))) > 0)
	//{
	//	write(STDOUT_FILENO, buffer, bytes);
	//}
	//close(fd);

}

void	redirect_to_stdin(const char *file)
{
	//write(tmp_fd, "Hello\nworld!\n", ft_strlen("Hello\nworld!\n"));
	//close(tmp_fd);
	//Open file in child process and redirect to stdin.
	pid_t pid = fork();
	if (pid == 0)
	{
		int fd = open(file, O_RDONLY);
		dup2(fd, STDIN_FILENO);
		close(fd);
		//Execute the command
		char *cmd = "/bin/cat";
		char *args[] = {cmd, NULL};
		execve(cmd, args, NULL);
	}
	else
	{
		wait(NULL);
		unlink(file);
	}
}

//int	read_heredoc(const char *delimiter)
//{
//	char	*line;
//	int		pfd[2];
//
//	if (pipe(pfd) < 0)
//		fprintf(stderr, "pipe error\n");
//	while (1)
//	{
//		line  = readline("> ");
//		if (line == NULL)
//			break ;
//		if (ft_strcmp(line, delimiter) == 0)
//		{
//			free(line);
//			break ;
//		}
//		dprintf(pfd[1], "%s\n", line);
//		free(line);
//	}
//	close(pfd[1]);
//	return (pfd[0]);
//}

bool	analyze_tokens(t_token *head)
{
	int		paren;
	const char	*heredoc_file;

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
			heredoc_file = read_heredoc(head->literal);
			redirect_to_stdin(heredoc_file);
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
