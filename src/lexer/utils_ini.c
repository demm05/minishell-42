/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ini.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelnyk <dmelnyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:26:24 by dmelnyk           #+#    #+#             */
/*   Updated: 2025/03/12 15:32:41 by dmelnyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./lexer_private.h"
#include "libft.h"
#include <stdlib.h>

t_lexer	*new_lexer(const char *str)
{
	t_lexer	*l;

	if (!str || !*str)
		return (NULL);
	l = malloc(sizeof(t_lexer));
	if (!l)
		return (NULL);
	ft_memset(l, 0, sizeof(t_lexer));
	l->input = str;
	l->size = ft_strlen(str);
	read_char(l);
	return (l);
}

t_token	*new_token(t_token_type type, char *s)
{
	t_token	*tok;

	tok = malloc(sizeof(t_token));
	if (!tok)
		return (NULL);
	tok->type = type;
	tok->literal = s; 
	tok->next = NULL;
	tok->prev = NULL;
	return (tok);
}

/**
 * @brief Appends a token to the lexer's token list
 *
 * This function adds a new token to the circular doubly linked list of tokens
 * in the lexer. If the token list is empty, the new token becomes the first token
 * and points to itself in prev. Otherwise, the token is inserted at the end of
 * the list, maintaining the circular structure.
 *
 * @param l Pointer to the lexer
 * @param new Token to append
 * @return int 0 on success, 1 if lexer is NULL, 0 if new token is NULL
 */
int	append_token(t_lexer *l, t_token *new)
{
	if (!l)
		return (1);
	if (!new)
		return (0);
	if (!l->tokens)
	{
		new->prev = new;
		l->tokens = new;
	}
	else
	{
		new->prev = l->tokens->prev;
		l->tokens->prev->next = new;
		l->tokens->prev = new;
	}
	return (0);
}

/**
 * @brief Creates a token with allocated memory for its literal value and appends it to the lexer
 *
 * This function allocates a buffer of the specified size, copies characters from the
 * lexer's current position into the buffer, creates a new token with this buffer as
 * its literal value, advances the lexer's position, and appends the token to the lexer.
 *
 * @param l Pointer to the lexer
 * @param type The type of the token to create
 * @param size The size of memory to allocate for the token's literal value
 * @return int 0 on success, 1 if lexer is NULL, memory allocation fails, or token creation fails
 */
int	append_alloc(t_lexer *l, t_token_type type, int size)
{
	t_token	*new;
	char	*s;
	int		i;
	int		j;

	if (!l)
		return (1);
	s = malloc(sizeof(char) * (size + 1));
	if (!s)
		return (1);
	i = 0;
	j = l->position;
	while (i < size && j < l->size)
		s[i++] = l->input[j++];
	s[i] = 0;
	new = new_token(type, s);
	if (!new)
		free(s);
	l->read_postion += size - 1;
	read_char(l);
	return (append_token(l, new));
}

/**
 * @brief Creates a token with the given literal and advances the lexer position
 *
 * This function creates a new token with the provided literal and type, advances
 * the lexer by the specified number of positions, and appends the token to the lexer.
 * If the literal is NULL, its size is treated as 0.
 *
 * @param l Pointer to the lexer
 * @param literal The literal string value for the token (will be freed on error)
 * @param advance Number of positions to advance the lexer
 * @param type The type of the token to create
 * @return int 0 on success, 1 if lexer is NULL, memory allocation fails, or token creation fails
 */
int	append_advance(t_lexer *l, char *literal, unsigned int advance, t_token_type type)
{
	t_token			*new;
	unsigned int	size;

	if (!l)
	{
		free(literal);
		return (1);
	}
	if (!literal)
		size = 0;
	else
		size = ft_strlen(literal);
	new = new_token(type, literal);
	if (!new)
	{
		free(literal);
		return (1);
	}
	if (advance)
	{
		l->read_postion += advance - 1;
		read_char(l);
	}
	return (append_token(l, new));
}

void	free_lexer(t_lexer *l)
{
	t_token	*next;

	if (!l)
		return ;
	while (l->tokens)
	{
		next = l->tokens->next;
		free(l->tokens);
		l->tokens = next;
	}
	free(l);
}
