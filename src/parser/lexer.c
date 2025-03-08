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
//				append_token(l, OR, 2);
			else
				append_advance(l, NULL, 1, PIPE);
				//append_token(l, PIPE, 1);
		}
		else if (l->ch == '&')
		{
			if (peek_char(l) == '&')
				append_advance(l, NULL, 2, AND);
				//append_token(l, AND, 2);
			else
				append_advance(l, NULL, 2, ILLEGAL);
				//append_token(l, ILLEGAL, 2);
		}
		else if (l->ch == '>')
		{
			if (peek_char(l) == '>')
				append_advance(l, NULL, 2, REDIR_OUT_A);
				//append_token(l, REDIR_OUT_A, 2);
			else
				append_advance(l, NULL, 1, REDIR_OUT);
				//append_token(l, REDIR_OUT, 1);
		}
		else if (l->ch == '<')
		{
			if (peek_char(l) == '<')
				append_advance(l, NULL, 2, HERE_DOC);
//				append_token(l, HERE_DOC, 2);
			else
				append_advance(l, NULL, 1, REDIR_IN);
//				append_token(l, REDIR_IN, 1);
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
	append_token(l, EOL, 0);
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
	append_token(l, WORD, i);
}

