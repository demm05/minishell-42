#ifndef EXPANSION_H 
# define EXPANSION_H 

typedef struct s_astnode	t_astnode;
typedef struct s_data		t_data;

void	expand_head(t_astnode *head, t_data *data);
char	*getenv_key(const char *s);

#endif
