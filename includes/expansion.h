#ifndef EXPANSION_H
# define EXPANSION_H

# include <stdlib.h>

# include "libft.h"
# include "minishell_c.h"
# include "parser.h"
# include "expand_struct.h"
# include "word_splitting.h"
# include "param.h"

void	expansion(t_parsed *parsed, t_envlist *envlist);

#endif
