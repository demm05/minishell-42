/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_refactor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelnyk <dmelnyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 18:16:50 by dmelnyk           #+#    #+#             */
/*   Updated: 2025/03/12 20:32:34 by dmelnyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./eval_private.h"
#include "../ast/ast.h"
#include <stdlib.h>

void	construct_dquote(t_data *data, t_astnode *head);

static void	expand_node(t_data *data, t_astnode *node)
{
	t_env	*env;

	env = getenv_val(data->env, node->literal);
	free(node->literal);
	if (env)
		node->literal = ft_strdup(env->value);
	else
		node->literal = ft_strdup("");
}

void	expand_tree(t_data *data, t_astnode *parent)
{
	t_astnode	**to_delete;
	t_astnode	**put_back;
	t_astnode	*cur;
	int			td;
	int			pb;
	bool		is_echo;

	if (!data || !parent || !parent->children)
		return ;
	to_delete = malloc(sizeof(t_astnode **) * parent->childs);
	if (!to_delete)
		return ;
	put_back = malloc(sizeof(t_astnode **) * parent->childs);
	if (!put_back)
	{
		free(to_delete);
		return ;
	}
	td = 0;
	pb = 0;
	is_echo = parent->type == ECHO;
	cur = parent->children;
	while (cur)
	{
		if (cur->type == SSPACE && !is_echo)
			to_delete[td++] = cur;
		else if (cur->type == EXPAND_VAR)
		{
			expand_node(data, cur);
			cur->type = WORD;
			put_back[pb++] = cur;
		}
		else if (cur->type == DQUOTE)
		{
			put_back[pb++] = cur;
			construct_dquote(data, cur);
			cur = cur->next;
			while (cur && cur->type != DQUOTE)
			{
				to_delete[td++] = cur;
				cur = cur->next;
			}
			if (cur && cur->type == DQUOTE)
				to_delete[td++] = cur;
		}
		else
			put_back[pb++] = cur;
		if (cur)
			cur = cur->next;
	}
	int	i = 0;
	while (i < td)
	{
		if (to_delete[i]->literal) // Add this null check
			free(to_delete[i]->literal);
		free(to_delete[i++]);
	}
	free(to_delete);
	parent->children = NULL;
	i = 0;
	while (i < pb)
	{
		put_back[i]->prev = NULL;
		put_back[i]->next = NULL;
		add_child(parent, put_back[i++]);
	}
	free(put_back);
}

// I guess I should remeke this function
// Because it's the same like within space tokens
// They can serve as dquote token
// So it will be more generilezed
void	construct_dquote(t_data *data, t_astnode *head)
{
	t_astnode	*cur;
	char		*res;
	int			len;
	int			j;
	int			k;

	if (!data || !head || head->type != DQUOTE)
		return ;
	head->type = WORD;
	cur = head->next;	
	len = 0;
	while (cur && cur->type != DQUOTE)
	{
		if (cur->type == EXPAND_VAR)
			expand_node(data, cur);
		if (cur->literal)
			len += ft_strlen(cur->literal);
		cur = cur->next;
	}
	// TODO: some error
	if (cur->type != DQUOTE)
		return ;
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return ;
	j = 0;
	cur = head->next;
	while (cur && cur->type != DQUOTE)
	{
		k = 0;
		if (cur->literal)
		{
			while (cur->literal[k])
				res[j++] = cur->literal[k++];
		}
		cur = cur->next;
	}
	res[j] = 0;
	free(head->literal);
	head->literal = res;
}
