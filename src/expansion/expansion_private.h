#ifndef EXPANSION_PRIVATE_H 
# define EXPANSION_PRIVATE_H 

# include "../ast/ast.h"

bool	is_valid_envv(const char *s);

void	lex_wildcard(t_lexer *l);
void	lex_quote(t_lexer *l);
void	lex_word(t_lexer *l);
void	lex_env(t_lexer *l);
t_token	*word_generate_tokens(char *line, t_data *data);

void	expand_variable(t_lexer *l, char *key, bool is_status, int size);

void	do_child(t_astnode *head, t_astnode *cur, t_data *data);
void	do_head(t_astnode *head, t_data *data);

char	**join_tokens(t_token **head);
t_token	**split_tokens(t_token *head);

#endif
