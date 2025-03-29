/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   by: dmelnyk <dmelnyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   created: 2025/03/12 11:18:36 by dmelnyk           #+#    #+#             */
/*   Updated: 2025/03/22 11:47:41 by dmelnyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef minishell_h
# define minishell_h

#include <stdbool.h>
#include "libft.h"

typedef struct s_lexer		t_lexer;
typedef struct s_astnode	t_astnode;
typedef struct s_env		t_env;
typedef struct s_token		t_token;

typedef struct s_data
{
	char					*prompt;
	char					*line;
	t_astnode				*head;
	t_env					*env;
	int						exit_status;
	int						signal;
}	t_data;

void	exec(t_data *data);

/**
 * @brief Main input reading loop.
 * Handles multi-line input, signals, and history.
 *
 * @param data A pointer to the t_data structure.
 */
void	mini_read(t_data *data);
void	reset_signals(void);

typedef enum e_tokentype
{
	EOL,		// End of line
	ILLEGAL,	// When invalid input
	EXIT_STATUS,// $?
	AND,		// &&
	OR,			// ||
	REDIR_OUT,	// >
	REDIR_IN,	// <
	REDIR_OUT_A,// >>
	HERE_DOC,	// <<	
	PIPE,		// |
	EXEC,		// Executable like ls wc grep 
	WORD,		// It could be an argument or file
	PATH,		// Can be relative or absolute eg ./ or /
	LPAREN,		// (
	RPAREN,		// )
	WILDCARD,	// *
	EXPAND_VAR,	// $ better
	QUOTE,
	SSPACE,
	SEQUENCE,
	// Built in shell exec
	CD,
	ECHO,
	PWD,
	EXPORT,		
	UNSET,
	ENV,
	EXIT,
}	t_token_type;

#endif
