/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assemble_ast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelnyk <dmelnyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 12:37:48 by dmelnyk           #+#    #+#             */
/*   Updated: 2025/03/18 12:38:23 by dmelnyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ast_private.h"
#include "../extra/extra.h"
#include "libft.h"

typedef struct	s_state
{
	bool	dquote;
	bool	squote;
	bool	escape;
}	t_state;

void	assemble_head(t_astnode *head, t_data *data)
{
	if (!head || !data)
		return ;
}

static unsigned int	get_env_len(char *key, t_data *data)
{
	t_env	*env;
	if (!key || !data)
		return (0);
	env = getenv_val(data->env, key);
	if (!env || !env->value)
		return (0);
	return (ft_strlen(env->value));
}


static unsigned int	get_key(char *s)
{
	return (0);
}

/*
static unsigned int	get_len(char *s, t_data *data)
{
	unsigned int	len;
	t_state			st;

	len = 0;
	ft_bzero(&st, sizeof(t_state));
	while (*s)
	{
		if (st.dquote)
		{
			if (*s == '"')
				st.dquote = !st.dquote;
		}
		if (*s == '"' && !st.squote)
			st.dquote = !st.dquote;
		else if (*s == '\'' && !st.dquote)
			st.dquote = !st.squote;
		
	//	if (!st.squote && !st.dquote && *s == '$')
	//		len += get_env_len()
	}
}*/
