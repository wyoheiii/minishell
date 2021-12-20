#ifndef DEBUG_H
# define DEBUG_H

# include <stdbool.h>
# include <stdlib.h>

# include "libft.h"
# include "lexer.h"
# include "parser.h"

void	print_token_list(t_list *token_list);
void	print_parsed(t_parsed *parsed);

#endif
