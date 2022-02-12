#ifndef EXPAND_ARGV_H
# define EXPAND_ARGV_H

# include <stdbool.h>
# include <stdlib.h>

# include "libft.h"
# include "expand_struct.h"
# include "word_splitting.h"
# include "not_param_str.h"
# include "expand_is.h"
# include "expand_param.h"
# include "minishell_c.h"

t_expand	*expand_argv(t_expand *list, t_envlist *envlist);

#endif
