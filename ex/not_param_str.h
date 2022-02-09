#ifndef NOT_PARAM_STR_H
# define NOT_PARAM_STR_H

# include <stdlib.h>

# include "libft.h"
# include "expand_struct.h"

char	*string_before_param(t_expand *list, char **line);
char	*join_remaining_string(t_expand *list, char **line);

#endif
