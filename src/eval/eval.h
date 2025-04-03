/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelnyk <dmelnyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:26:56 by dmelnyk           #+#    #+#             */
/*   Updated: 2025/03/12 12:48:45 by dmelnyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVAL_H
# define EVAL_H

# include <stdbool.h>

typedef struct s_astnode	t_astnode;
typedef struct s_data		t_data;

void	exec(t_data *data);

#endif
