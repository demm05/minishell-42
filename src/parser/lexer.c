#include "../../inc/parser.h"

static void	add_word(t_lexer *l);

void	generate_tokens(t_lexer	*l)
{
	if (!l)
		return ;
	while (l->position < l->size)
	{
		eat_whitespaces(l);
		if (!l->ch)
			break ;
		else if (l->ch == '$')
			lex_env_var(l);
		if (l->ch == '\'' || l->ch == '"')
			lex_quote(l);
		else if (l->ch == '|')
		{
			if (peek_char(l) == '|')
				append_advance(l, NULL, 2, OR);
			else
				append_advance(l, NULL, 1, PIPE);
		}
		else if (l->ch == '&')
		{
			if (peek_char(l) == '&')
				append_advance(l, NULL, 2, AND);
			else
				append_advance(l, NULL, 2, ILLEGAL);
		}
		else if (l->ch == '>')
		{
			if (peek_char(l) == '>')
				append_advance(l, NULL, 2, REDIR_OUT_A);
			else
				append_advance(l, NULL, 1, REDIR_OUT);
		}
		else if (l->ch == '<')
		{
			if (peek_char(l) == '<')
				append_advance(l, NULL, 2, HERE_DOC);
			else
				append_advance(l, NULL, 1, REDIR_IN);
		}
		else if (!is_there_exec(l))
		{
			if (lex_keyword(l))
				continue ;
			else if (lex_executable(l))
				continue ;
		}
		else
			add_word(l);
	}
	append_advance(l, NULL, 0, EOL);
}

/**
 * @brief Adds a WORD token to the lexer's token list.
 *
 * Extracts a word from input, stops at delimiters.
 *
 * @param l Pointer to the lexer struct.
 */
static void	add_word(t_lexer *l)
{
	int		i;
	int		w;
	char	c;

	w = get_pos_next_whitespace(l);
	i = 0;
	while (i < w)
	{
		c = l->input[l->position + i];
		if (c == '|' || c == '&')
			break ;
		i++;
	}
	append_alloc(l, WORD, i);
}
