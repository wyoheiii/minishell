#ifndef DELIMITER_H
# define DELIMITER_H

# include <stdbool.h>
# include <stdlib.h>

# include "libft.h"
# include "parser.h"

bool	is_delimiter(char *str);
size_t	get_delimiter_count(t_list *token_list);
int		get_state(char *str);

#endif
