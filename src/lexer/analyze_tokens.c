/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyze_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelnyk <dmelnyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:13:10 by dmelnyk           #+#    #+#             */
/*   Updated: 2025/03/12 12:25:52 by dmelnyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./lexer.h"
#include <stdio.h>

static void	show_where_illegal(t_token *ileg, t_lexer *l)
{
	int	i;
	int	len;

	printf("%s\n", l->input);
	len = ileg->literal - l->input;
	i = 0;
	while (i++ < len)
		printf(" ");
	printf("^\n");
	i = 0;
	while (i++ < len)
		printf(" ");
	printf("illegal token type\n");
}

int	analyze_tokens(t_lexer *l)
{
	t_token	*token;

	token = l->tokens;
	while (token)
	{
		if (token->type == ILLEGAL)
		{
			//show_where_illegal(token, l);
			return (1);
		}
		token = token->next;
	}
	return (0);
}
