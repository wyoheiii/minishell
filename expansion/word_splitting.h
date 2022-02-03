#ifndef WORD_SPLITTING_H
# define WORD_SPLITTING_H

# include <stdlib.h>

# include "libft.h"
# include "libft_utils.h"
# include "list_utils.h"

# define DELIMITER " \t\n"

t_list	*word_splitting(char *str);

#endif
