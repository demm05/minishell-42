/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   by: dmelnyk <dmelnyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   created: 2025/03/12 11:18:36 by dmelnyk           #+#    #+#             */
/*   Updated: 2025/03/22 11:47:41 by dmelnyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef minishell_h
# define minishell_h

# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include "libft.h"
# include "../src/ast/ast.h"
# include "../src/enviroment/enviroment.h"
# include "../src/eval/eval.h"
# include "../src/expansion/expansion.h"
# include "../src/extra/extra.h"
# include "../src/lexer/lexer.h"
# include "../src/tokenize_line/tok.h"
# include "../src/heredoc/heredoc.h"

typedef struct s_data
{
	char					*prompt;
	char					*line;
	t_astnode				*head;
	t_env					*env;
	t_tmp					*tmp;
	int						exit_status;
}	t_data;

#endif
