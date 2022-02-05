#ifndef LIBFT_UTILS_H
# define LIBFT_UTILS_H

# include <stdlib.h>

# include "libft.h"

char	*my_substr(char *str, size_t start, size_t length);
char	*my_strdup(char *str);
char	*my_strjoin(char **s1, char **s2);
void	*my_calloc(size_t count, size_t size);

#endif
