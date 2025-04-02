#ifndef EXPANSION_PRIVATE_H 
# define EXPANSION_PRIVATE_H 

# include "../ast/ast.h"
# include "./expansion.h"

t_token_type	get_exec_type(char *s);
t_astnode		*create_nodes(char **ss);
char			**expand_word(t_astnode *head, t_data *data, bool spilt_it);
t_token			*word_generate_tokens(char *line, t_data *data);
t_token			**split_tokens(t_token *head);
char			**join_tokens(t_token **head);

#endif
