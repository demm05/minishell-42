/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_private.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelnyk <dmelnyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:11:31 by dmelnyk           #+#    #+#             */
/*   Updated: 2025/03/12 15:37:53 by dmelnyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_PRIVATE_H
# define LEXER_PRIVATE_H

# include "./lexer.h"

typedef struct s_keyword
{
	const char		*key;
	t_token_type	type;
	int				size;
}	t_keyword;

/**
 * @brief Creates a new token with the specified type and literal value
 *
 * @param type The type of the token
 * @param s The literal string value of the token
 * @return t_token* Pointer to the newly created token, or NULL if fails
 */
t_token	*new_token(t_token_type type, char *s);

/**
 * @brief Appends a token to the lexer's token list
 *
 * @param l Pointer to the lexer
 * @param token Token to append
 * @return int 0 on success, 1 on error
 */
int		append_token(t_lexer *l, t_token *token);

/**
 * @brief Creates a token with allocated memory for its literal value
 * and appends it to the lexer
 *
 * @param l Pointer to the lexer
 * @param type The type of the token to create
 * @param size The size of memory to allocate for the token's literal value
 * @return int 0 on success, 1 on error
 */
int		append_alloc(t_lexer *l, t_token_type type, int size);

/**
 * @brief Creates a token with the given literal and advances the lexer position
 *
 * @param l Pointer to the lexer
 * @param literal The literal string value for the token
 * @param advance Number of positions to advance the lexer
 * @param type The type of the token to create
 * @return int 0 on success, 1 on error
 */
int		append_advance(t_lexer *l, char *literal, unsigned int advance, t_token_type type);

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

/**
 * @brief Calculates the distance to the next whitespace or end of input.
 *
 * @param l A pointer to the `t_lexer` structure.
 * @return The number of characters to the next whitespace or end of input.
 */
int		get_pos_next_whitespace(t_lexer *l);
int		is_there_exec(t_lexer *l);
int		lex_executable(t_lexer *l);
int		lex_word(t_lexer *l);
int		lex_env_var(t_lexer *l);
int		lex_keyword(t_lexer *l);
int		lex_quote(t_lexer *l);
void	free_lexer(t_lexer *l);

#endif
