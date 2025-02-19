# include "../inc/parser.h"

char	*decode(t_token_type t);

int	main(int argc, char **argv)
{
	t_lexer	*l;
	t_token	*t;
	char	*line;
	int		i;
	int		exit_s = 0;

	while (!exit_s)
	{
		line = readline("Promt > ");
		if (!line)
			break ;
		l = new_lexer(line);
		generate_tokens(l);
		t = l->tokens;
		while (t)
		{
			if (t->type == EXIT)
				exit(0);
			printf("Type: %s\t\tLiteral: ", decode(t->type));
			i = 0;
			while (i < t->size)
				printf("%c", t->literal[i++]);
			printf("\n");
			t = t->next;
		}
		//free(line);
		//free_lexer(l);
	}
	return (0);
}

char *decode(t_token_type t)
{
	switch (t)
	{
		case ECHO: return "ECHO";
		case LT: return "LT";
		case GT: return "GT";
		case DLT: return "DLT";
		case DGT: return "DGT";
		case DSIGN: return "DSIGN";
		case RPATH: return "RPATH";
		case ABSPATH: return "ABSPATH";
		case EOL: return "EOL";
		case ILLEGAL: return "ILLEGAL";
		case EXIT_STATUS: return "EXIT_STATUS";
		case SQUOTE: return "SQUOTE";
		case DQUOTE: return "DQUOTE";
		case AND: return "AND";
		case OR: return "OR";
		case REDIR_OUT: return "REDIR_OUT";
		case REDIR_IN: return "REDIR_IN";
		case REDIR_OUT_A: return "REDIR_OUT_A";
		case HERE_DOC: return "HERE_DOC";
		case PIPE: return "PIPE";
		case VAR_EXP: return "VAR_EXP";
		case EXEC: return "EXEC";
		case WORD: return "WORD";
		case CD: return "CD";
		case PWD: return "PWD";
		case EXPORT: return "EXPORT";
		case UNSET: return "UNSET";
		case ENV: return "ENV";
		case EXIT: return "EXIT";
		default: return "UNKNOWN";
	}
}

