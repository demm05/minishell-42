/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment_private.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelnyk <dmelnyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 18:20:59 by dmelnyk           #+#    #+#             */
/*   Updated: 2025/04/07 18:23:10 by dmelnyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIROMENT_PRIVATE_H
# define ENVIROMENT_PRIVATE_H

# include "minishell.h"

t_env	*env_append(t_env **head, char *key, char *value);

#endif
