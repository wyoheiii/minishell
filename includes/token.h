#ifndef TOKEN_H
# define TOKEN_H

# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>

# include "libft.h"
# include "flag.h"
# include "utils.h"

char	*get_token(const char *line, size_t *index, size_t size);

#endif
