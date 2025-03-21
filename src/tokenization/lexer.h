/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelnyk <dmelnyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:04:12 by dmelnyk           #+#    #+#             */
/*   Updated: 2025/03/21 14:19:29 by dmelnyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

#include "../../inc/minishell.h"
#include <stdbool.h>

typedef struct s_token
{
	int					size;
	t_token_type		type;
	char				*literal;
	struct s_token		*next;
	struct s_token		*prev;
}	t_token;

typedef struct s_lexer
{
	const char	*input;
	t_token		*tokens;
	// current position in input (points to current char)
	int			position;
	// current reading position in input (after current char)
	int			read_postion;
	// lenght of input
	int			size;
	// current char under examination(poistiob)
	char		ch;
}	t_lexer;

char	*decode(t_token_type t);
void	generate_tokens(t_data *data);
bool	is_token_exec(t_token_type t);
bool	analyze_tokens(t_token *head);
void	print_tokens(t_token *token);
void	free_tokens(t_token **head);
bool	match(t_token *token, t_token_type expected[], int size);
bool	is_redir(t_token_type t);

#endif
