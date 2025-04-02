#ifndef EXPANSION_H 
# define EXPANSION_H 

# include "../ast/ast.h"

char	**ft_splitc(char *str, char *charset);

void	expand_head(t_astnode *head, t_data *data);

#endif
