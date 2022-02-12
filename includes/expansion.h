#ifndef EXPANSION_H
# define EXPANSION_H

# include <stdlib.h>

# include "libft.h"
# include "minishell_c.h"
# include "parser.h"
# include "expand_struct.h"
# include "expand_argv.h"

void	expansion(t_parsed *parsed, t_envlist *envlist);

#endif
