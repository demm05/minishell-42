/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_private.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelnyk <dmelnyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 18:23:54 by dmelnyk           #+#    #+#             */
/*   Updated: 2025/04/07 18:23:57 by dmelnyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_PRIVATE_H 
# define EXPANSION_PRIVATE_H 

# include "minishell.h"

t_token_type	get_exec_type(char *s);
t_astnode		*create_nodes(char **ss);
char			**expand_word(t_astnode *head, t_data *data, bool spilt_it);
t_token			*word_generate_tokens(char *line, t_data *data);
t_token			**split_tokens(t_token *head);
char			**join_tokens(t_token **head);
void			lex_env(t_lexer *l, bool to_split);
bool			is_valid_envv(const char *s);

#endif
