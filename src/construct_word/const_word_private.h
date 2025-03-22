/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   const_word_private.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelnyk <dmelnyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 11:34:44 by dmelnyk           #+#    #+#             */
/*   Updated: 2025/03/22 19:21:18 by dmelnyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONST_WORD_PRIVATE_H
# define CONST_WORD_PRIVATE_H

#include "const_word.h"
#include "../lexer/lexer.h"

t_token	*word_generate_tokens(char *line);
void	lex_wildcard(t_lexer *l);
void	lex_quote(t_lexer *l);
void	lex_word(t_lexer *l);
void	lex_env(t_lexer *l);
bool	is_valid_envv(const char *s);
char	**expand_word(t_astnode *head, t_data *data);
void	expand_variables(t_token *tok, t_data *data);
t_token	**wildcard_it(t_token *head);
char	**join_tokens(t_token **head);

#endif
