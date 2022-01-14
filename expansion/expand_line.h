#ifndef EXPAND_LINE_H
# define EXPAND_LINE_H

# include <stdlib.h>
# include <stdbool.h>

# include "variable_name.h"
# include "expand_param.h"
# include "utils.h"
# include "libft.h"

# define NONE	0
# define SINGLE 1
# define DOUBLE 2

char	*get_expanded_line(char **command, size_t *count);

#endif
