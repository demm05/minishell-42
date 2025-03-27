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
	t_data		*data;
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
void	print_tokens(t_token *token);
void	free_tokens(t_token **head);
bool	match(t_token *token, t_token_type expected[], int size);
bool	is_redir(t_token_type t);
bool	is_token_exec(t_token_type t);

/**
 * @brief Creates a new token with the specified type and literal value
 *
 * @param type The type of the token
 * @param s The literal string value of the token
 * @return t_token* Pointer to the newly created token, or NULL if fails
 */
t_token	*new_token(t_token_type type, char *s, unsigned int size);

/**
 * @brief Appends a token to the lexer's token list
 *
 * @param l Pointer to the lexer
 * @param token Token to append
 * @return int 0 on success, 1 on error
 */
t_token	*append_token(t_lexer *l, t_token *token);

/**
 * @brief Creates a token with allocated memory for its literal value
 * and appends it to the lexer
 *
 * @param l Pointer to the lexer
 * @param type The type of the token to create
 * @param size The size of memory to allocate for the token's literal value
 * @return int 0 on success, 1 on error
 */
t_token	*append_alloc(t_lexer *l, t_token_type type, int size);

/**
 * @brief Creates a token with the given literal and advances the lexer position
 *
 * @param l Pointer to the lexer
 * @param literal The literal string value for the token
 * @param advance Number of positions to advance the lexer
 * @param type The type of the token to create
 * @return int 0 on success, 1 on error
 */
t_token	*append_advance(t_lexer *l, char *literal, unsigned int advance, t_token_type type);

/**@brief Reads the next character from the input.
 * Updates internal pointers and the current character (`ch`).
 *
 * @param l A pointer to the t_lexer structure.
 */
void	read_char(t_lexer *l);

/**@brief Returns the next character without consuming it.
 *
 * @param l A pointer to the t_lexer structure.
 * @return The next character or 0 at the end of input.
 */
char	peek_char(t_lexer *l);

/**@brief Skips whitespace characters.
 *
 * @param l A pointer to the t_lexer structure.
 */
void	eat_whitespaces(t_lexer *l);

#endif
