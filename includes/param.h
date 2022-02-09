#ifndef PARAM_H
# define PARAM_H

# include <stdlib.h>

# include "libft.h"
# include "expand_struct.h"
# include "minishell_c.h"

char	*get_variable_name(char *line, size_t *start);
char	*param_func(t_expand *list, t_envlist *envlist);

#endif
