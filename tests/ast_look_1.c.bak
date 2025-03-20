/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_look_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelnyk <dmelnyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 18:21:01 by dmelnyk           #+#    #+#             */
/*   Updated: 2025/03/15 18:35:32 by dmelnyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/test.h"

t_astnode	*head = NULL;
char		*argv[] = {"./minishell"};
t_lexer		*l = NULL;
t_astnode	*head;

Test(redir, test_1)
{
	char	*s = "ping -c 5 1.1.1.1 | grep tll > a";

	l = new_lexer(s);
	cr_assert_not_null(l);
	generate_tokens(l);
	head = parse(l);
	cr_assert_not_null(head);
	cr_assert(head->type == REDIR_OUT);
	cr_assert_not_null(head->children);
	cr_assert(head->children->type == PIPE);
	cr_assert(head->children->childs == 2);
}

Test(redir, test_2)
{
	char	*s = "< a < b cat > c > d";

	l = new_lexer(s);
	cr_assert_not_null(l);
	generate_tokens(l);
	head = parse(l);
	cr_assert_not_null(head);
	cr_assert(head->type == REDIR_OUT);
	cr_assert_not_null(head->children);
	cr_assert(head->childs == 2);
	cr_assert(head->children->type == REDIR_IN || head->children->next->type == REDIR_IN);
}

Test(invalid, test_1)
{
	char	*s = "< ";
	l = new_lexer(s);
	generate_tokens(l);
}
