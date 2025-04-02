#include "expansion_private.h"

t_token	*word_generate_tokens(char *line, t_data *data)
{
	t_lexer	l;

	ft_bzero(&l, sizeof(t_lexer));
	l.input = line;
	l.size = ft_strlen(line);
	l.data = data;
	read_char(&l);
	while (l.position < l.size)
	{
		if (l.ch == '\'' || l.ch == '"')
			lex_quote(&l);
		else if (l.ch == '*')
			lex_wildcard(&l);
	//	else if (private_env_tes(l.input + l.position, &l))
	//		//lex_env(&l);
		else
			lex_word(&l);
	}
	return (l.tokens);
}

