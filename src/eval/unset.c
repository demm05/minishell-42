/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelnyk <dmelnyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:40:16 by dmelnyk           #+#    #+#             */
/*   Updated: 2025/03/12 12:48:29 by dmelnyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./eval_private.h"
#include "../extra/extra.h"
void	remove_env(t_env **head, char *key)
{
	t_env	*prev;
	t_env	*next;
	t_env	*target_node;

	if (!head || !*head || !key)
		return ;
	target_node = getenv_val(*head, key);
	if (!target_node)
		return ;
	prev = target_node->prev;
	next = target_node->next;
	free(target_node->key);
	free(target_node->value);
	if (target_node == *head)
	{
		free(*head);
		*head = next;
		return ;
	}
	free(target_node);
	if (prev)
		prev->next = next;
	else if (!next)
		(*head)->prev = prev;
}

char	*extract_key(char *arg)
{
	char	*equal_sign;
	char	*key;

	key = arg;
	equal_sign = ft_strchr(key, '=');
	if (equal_sign)
		*equal_sign = '\0';
	return (key);
}

#include <stdio.h>
bool	handle_unset(t_astnode *head, t_data *data)
{
	if (!head->children)
		return (0);
	//t_astnode *head1 = head;
	//handle_export(head1, data);
	char *key = extract_key(head->children->literal);
	//t_env *cur = data->env;
	remove_env(&data->env, key);
	//while (cur)
	//{
	//	printf("%s\n", cur->key);
	//	if (cur->key == key)
	//		printf("hhhh");
	//	cur = cur->next;
	//}
	return (0);
}
