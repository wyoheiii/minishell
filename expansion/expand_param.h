#ifndef EXPAND_PARAM_H
# define EXPAND_PARAM_H

# include <stdlib.h>
# include <stdbool.h>

# include "variable_name.h"
# include "utils.h"
# include "libft.h"
# include "libft_utils.h"

char	*param_func(char *str, char *line, size_t *index, size_t *start);
void	string_before_param(char *str, char **line,
			size_t *index, size_t *start);

#endif
