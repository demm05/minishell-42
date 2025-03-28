/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelnyk <dmelnyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 12:04:07 by dmelnyk           #+#    #+#             */
/*   Updated: 2025/03/22 19:08:05 by dmelnyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "const_word_private.h"
#include "minishell.h"
#include <stdio.h>

static inline char	**expand_word(t_astnode *head, t_data *data)
{
	t_token	*token;
	t_token	**arr;
	char	**res;

	if (!head || !head->literal)
		return (NULL);
	token = word_generate_tokens(head->literal, data);
	if (!token)
		return (NULL);
	arr = split_tokens(token);
	//arr = wildcard_it(&token);
	res = join_tokens(arr);
	free(arr);
	return (res);
}

static inline void	set_type(t_astnode *head)
{
	char			*s;

	s = head->literal;
	if (ft_strcmp(s, "echo") == 0)
		head->type = ECHO;
	else if (ft_strcmp(s, "pwd") == 0)
		head->type = PWD;
	else if (ft_strcmp(s, "cd") == 0)
		head->type = CD;
	else if (ft_strcmp(s, "export") == 0)
		head->type = EXPORT;
	else if (ft_strcmp(s, "env") == 0)
		head->type = ENV;
	else if (ft_strcmp(s, "unset") == 0)
		head->type = UNSET;
	else if (ft_strcmp(s, "exit") == 0)
		head->type = EXIT;
}

static inline t_astnode	*create_nodes(char **ss)
{
	t_astnode	*res;
	t_token		t;
	int			i;

	if (!ss || !*ss)
		return (NULL);
	i = 0;
	t.type = WORD;
	res = NULL;
	while (ss[i])
	{
		t.literal = ss[i];
		t.size = ft_strlen(ss[i]);
		append_astnode(&res, new_astnode(&t));
		i++;
	}
	return (res);
}

static inline void	do_child(t_astnode *head, t_astnode *cur, char **s)
{
	t_astnode	*new;
	t_astnode	*next;
	t_astnode	*new_last;

	if (!s || !head || !cur)
		return ;
	free(cur->literal);
	cur->literal = *s;
	new = create_nodes(s + 1);
	free(s);
	if (!new)
		return ;
	next = cur->next;
	new_last = new->prev;
	if (!head->next)
		head->prev = new_last;
	else if (!next)
		new_last->next = NULL;
	else
	{
		next->prev = new_last;
		new_last->next = next;	
	}
	cur->next = new;
	new->prev = cur;
}

static inline void	do_head(t_astnode *head, char **s)
{
	t_astnode	*new;
	t_astnode	*old_last;

	if (!s || !head)
		return ;
	free(head->literal);
	head->literal = *s;
	set_type(head);	
	new = create_nodes(s + 1);
	free(s);
	if (!new)
		return ;
	if (!head->children)
	{
		head->children = new;
		return ;
	}
	new->prev->next = head->children;
	old_last = head->children->prev;
	head->children = new;
	head->children->prev = old_last;
}

void	expand_head(t_astnode *head, t_data *data)
{
	t_astnode	*cur;
	t_astnode	*next;

	if (!head || !data || !(head->type == WORD || head->type == PATH || head->type == EXEC))
		return ;
	do_head(head, expand_word(head, data));
	cur = head->children;
	while (cur)
	{
		next = cur->next;
		if (cur->type == WORD || cur->type == PATH || cur->type == EXEC)
			do_child(head->children, cur, expand_word(cur, data));
		cur = next;
	}
	//print_ast(head, 0);
}
