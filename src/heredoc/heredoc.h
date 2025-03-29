/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riyano <riyano@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 22:26:04 by riyano            #+#    #+#             */
/*   Updated: 2025/03/28 22:29:57 by riyano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H
#include "../../libft/libft/include/libft.h"
#include "../tokenize_line/tok.h"

char	*read_heredoc(t_token *head);
char	*generate_filename(void);

#endif
