/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelnyk <dmelnyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 17:17:59 by dmelnyk           #+#    #+#             */
/*   Updated: 2025/04/08 17:17:59 by dmelnyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion_private.h"

bool	is_there_wildcard(t_token *head);

bool	match_pattern(t_token *pattern, char *target)
{
	int	len;

	if (pattern == NULL && *target == 0)
		return (true);
	if (pattern == NULL)
		return (false);
	if (pattern->type != WORD && pattern->type != WILDCARD)
		return (match_pattern(pattern->next, target));
	if (pattern->type == WILDCARD)
	{
		if (pattern->next == NULL)
			return (true);
		while (*target)
			if (match_pattern(pattern->next, target++))
				return (true);
		return (match_pattern(pattern->next, target));
	}
	else if (pattern->type == WORD)
	{
		len = ft_strlen(pattern->literal);
		if (ft_strncmp(pattern->literal, target, len) == 0)
			return (match_pattern(pattern->next, target + len));
	}
	return (false);
}

static int	expand_wildcard(t_token *pattern, t_token **res, char **targets)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (targets[j])
	{
		if (pattern->literal && pattern->literal[0] != '.' && \
			targets[j][0] == '.')
			;
		else if (match_pattern(pattern, targets[j]))
			res[i++] = new_token(WORD, ft_strdup(targets[j]),
					ft_strlen(targets[j]));
		j++;
	}
	if (!i)
		res[i++] = pattern;
	else
		free_tokens(&pattern, 1);
	return (i);
}

static void	process_tokens(t_token **arr, t_token **res, char **targets)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (arr[++i])
	{
		if (is_there_wildcard(arr[i]))
			j += expand_wildcard(arr[i], res + j, targets);
		else
			res[j++] = arr[i];
	}
	res[j] = 0;
}

t_token	**wildcard_it(t_token **arr)
{
	char	**targets;
	t_token	**res;

	if (!arr)
		return (NULL);
	init_wildcards(arr, &targets, &res);
	if (!res)
		return (NULL);
	process_tokens(arr, res, targets);
	dir_free_list(targets);
	free(arr);
	return (res);
}
