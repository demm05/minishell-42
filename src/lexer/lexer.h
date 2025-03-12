/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelnyk <dmelnyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:04:12 by dmelnyk           #+#    #+#             */
/*   Updated: 2025/03/12 15:27:01 by dmelnyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

#include "../../inc/minishell.h"
#include <stdbool.h>

typedef struct s_token
{
	struct s_token	*next;
	struct s_token	*prev;
	char			*literal;
	t_token_type	type;
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

bool	is_token_exec(t_token_type t);
char 	*decode(t_token_type t);
void	print_tokens(t_token *token);
int		analyze_tokens(t_lexer *l);
void	free_lexer(t_lexer *l);
void	generate_tokens(t_lexer	*l);
t_lexer	*new_lexer(const char *str);

/**
 * @brief Creates a new lexer instance for the given input string
 *
 * @param str The input string to be tokenized
 * @return t_lexer* Pointer to the newly created lexer, or NULL if fails
 */
t_lexer	*new_lexer(const char *str);

#endif
