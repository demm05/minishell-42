/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   by: dmelnyk <dmelnyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   created: 2025/03/12 11:18:36 by dmelnyk           #+#    #+#             */
/*   Updated: 2025/03/12 15:39:57 by dmelnyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef minishell_h
# define minishell_h

typedef struct s_lexer		t_lexer;
typedef struct s_astnode	t_astnode;
typedef struct s_env		t_env;

typedef struct s_data
{
	char					*prompt;
	char					*line;
	t_lexer					*l;
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
	LT,			// <
	GT,			// >
	DLT,		// <<
	DGT,		// >>
	DSIGN,		// $
	RPATH,		// ./minishell
	ABSPATH,	// /bin
	SQUOTE,		// '
	DQUOTE,		// "
	SSPACE,
	// Better names
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
	EXPAND_VAR,	// $ better
	VAR_EXP,	// $
	EXEC,		// Executable like ls wc grep 
	WORD,		// It could be an argument or file
	PATH,		// Can be relative or absolute eg ./ or /
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
