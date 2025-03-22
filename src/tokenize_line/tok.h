/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelnyk <dmelnyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 11:16:07 by dmelnyk           #+#    #+#             */
/*   Updated: 2025/03/22 11:25:11 by dmelnyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOK_H 
# define TOK_H 

#include "../lexer/lexer.h"

t_token	*generate_tokens(char *line);
bool	analyze_tokens(t_token *head);

#endif
