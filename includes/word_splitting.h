#ifndef WORD_SPLITTING_H
# define WORD_SPLITTING_H

# include <stdlib.h>
# include <stdbool.h>

# include "libft.h"
# include "expand_struct.h"
# include "list_utils.h"
# include "utils.h"

# define DELIMITER " \t\n"

t_list	*word_splitting(char *str);
char	*func(t_expand **list, char **line, t_list *split);

#endif
