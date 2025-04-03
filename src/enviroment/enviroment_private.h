#ifndef ENVIROMENT_PRIVATE_H
# define ENVIROMENT_PRIVATE_H

# include "minishell.h"

t_env	*env_append(t_env **head, char *key, char *value);

#endif
