#ifndef LEXER_H
# define LEXER_H

# include "libft.h"

# define EOF_FLAG       1
# define NO_TOKEN_FLAG  2

t_list	*lexer(const char *line);

#endif
