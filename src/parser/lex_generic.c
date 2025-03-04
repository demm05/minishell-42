#include "../../inc/parser.h"

int	is_there_exec(t_lexer *l)
{
	t_token				*last;

	if (!l->tokens)
		return (0);
	last = l->tokens->prev;
	while (1)
	{
		if (is_token_exec(last->type))
			return (1);
		if (last->type == AND || last->type == OR || last->type == PIPE)
			break ;
		last = last->prev;
		if (!last->next)
			break ;
	}
	return (0);
}

int	lex_executable(t_lexer *l)
{
	append_token(l, EXEC, get_pos_next_whitespace(l));
	return (1);
}

int	lex_word(t_lexer *l)
{
	append_token(l, WORD, get_pos_next_whitespace(l));
	return (1);
}
