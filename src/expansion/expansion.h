#ifndef EXPANSION_H 
# define EXPANSION_H 

# include "../ast/ast.h"

void	expand_head(t_astnode *head, t_data *data);
char	*getenv_key(const char *s);

#endif
