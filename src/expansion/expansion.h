#ifndef EXPANSION_H 
# define EXPANSION_H 

typedef struct s_data		t_data;
typedef struct s_astnode	t_astnode;

char	**ft_splitc(char *str, char *charset);
void	expand_head(t_astnode *head, t_data *data);

#endif
