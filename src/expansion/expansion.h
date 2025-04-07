/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelnyk <dmelnyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 18:24:00 by dmelnyk           #+#    #+#             */
/*   Updated: 2025/04/07 18:24:00 by dmelnyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H 
# define EXPANSION_H 

typedef struct s_data		t_data;
typedef struct s_astnode	t_astnode;

char	**ft_splitc(char *str, char *charset);
void	expand_head(t_astnode *head, t_data *data);

#endif
