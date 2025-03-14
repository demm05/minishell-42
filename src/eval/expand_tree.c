/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelnyk <dmelnyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 13:30:43 by dmelnyk           #+#    #+#             */
/*   Updated: 2025/03/14 14:06:07 by dmelnyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./eval_private.h"
#include "../ast/ast.h"
#include <stdlib.h>

typedef struct	s_expand
{
	t_astnode	**to_delete;
	t_astnode	**to_keep;
	int			td;
	int			tk;
}	t_expand;

static void	expand_variable(t_data *data, t_astnode *node);
static void	join_nodes(t_data *data, t_astnode **head, t_token_type key);
static bool	init_expand(t_astnode *parent, t_expand *expand);
static int	len_of_combined_nodes(t_data *data, t_astnode *head, t_token_type key);
static void	mark_nodes(t_astnode *head, t_expand *exp, t_token_type key);

void	expand_tree(t_astnode *parent, t_data *data)
{
	t_astnode	*cur;
	t_expand	exp;
	int			i;

	if (!data || !parent || init_expand(parent, &exp))
		return ;
	cur = parent->children;
	while (cur)
	{
		i = 0;
		cur->type = WORD;
		mark_nodes(cur, &exp, SSPACE);
		join_nodes(data, &cur, SSPACE); 
	}
	i = 0;
	while (i < exp.td)
	{
		if (exp.to_delete[i]->literal)
			free(exp.to_delete[i]->literal);
		free(exp.to_delete[i++]);
	}
	i = 0;
	while (i < exp.tk)
		add_child(parent, exp.to_keep[i++]);
}

static void	mark_nodes(t_astnode *head, t_expand *exp, t_token_type key)
{
	exp->to_keep[exp->tk++] = head;
	head = head->next;
	while (head && head->type != key)
	{
		exp->to_delete[exp->td] = head;
		head = head->next;	
	}
}

static void	join_nodes(t_data *data, t_astnode **head, t_token_type key)
{
	t_astnode	*cur;
	char		*res;
	int			j;
	int			k;

	res = malloc(sizeof(char) * (len_of_combined_nodes(data, *head, key) + 1));
	if (!res)
	{
		*head = NULL;
		return ;
	}
	cur = *head;
	j = 0;
	while (cur && cur->type != key)
	{
		if (cur->literal)
		{
			k = 0;
			while (cur->literal[k])
				res[j++] = cur->literal[k++];
		}
		cur = cur->next;
	}
	res[j] = 0;
	free((*head)->literal);
	(*head)->literal = res;
	*head = cur;
}

static int	len_of_combined_nodes(t_data *data, t_astnode *head, t_token_type key)
{
	int	len;

	if (!head)
		return (0);
	len = 0;
	while (head && head->type != key)
	{
		if (head->type == EXPAND_VAR)
			expand_variable(data, head);
		if (head->literal)
			len += ft_strlen(head->literal);
		head = head->next;
	}
	return (len);
}

static bool	init_expand(t_astnode *parent, t_expand *expand)
{
	expand->to_delete = malloc(sizeof(t_astnode **) * parent->childs);
	if (!expand->to_delete)
		return (1);
	expand->to_keep = malloc(sizeof(t_astnode **) * parent->childs);
	if (!expand->to_keep)
	{
		free(expand->to_delete);
		return (1);
	}
	return (0);
}

static void	expand_variable(t_data *data, t_astnode *node)
{
	t_env	*env;

	if (!data || !node)
		return ;
	env = getenv_val(data->env, node->literal);
	free(node->literal);
	if (env)
		env->value = ft_strdup(env->value);
	else
		env->value = ft_strdup("");
	node->type = WORD;
}
