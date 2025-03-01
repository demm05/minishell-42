#include "../../inc/parser.h"

bool	ft_isspace(char ch)
{
	return (ch == ' ' || ch == '\t' || ch == '\r' || ch == '\n');
}

bool	is_token_exec(t_token_type t)
{
	if (t == EXEC || t == CD || t == ECHO || t == PWD)
		return (1);
	if (t == EXPORT || t == UNSET || t == ENV || t == EXIT)
		return (1);
	return (0);
}

char *decode(t_token_type t)
{
	switch (t)
	{
		case EXPAND_VAR: return "EXPAND_VAR";
		case PATH: return "PATH";
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

void	print_tokens(t_token *token)
{
	printf("Stream of tokens: ");
	while (token->next)
	{
		printf("%s -> ", decode(token->type));
		token = token->next;
	}
	printf("%s", decode(token->type));
	printf("\n\n");
}
