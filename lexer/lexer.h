#ifndef LEXER_H
# define LEXER_H

# include <stdbool.h>
# include <stdio.h>
# include "libft.h"

# define QUOTE_FLAG         1
# define DOUBLE_QUOTE_FLAG  2
# define VARIABLE_FLAG      4
# define REDIRECT_FLAG      8
# define PIPE_FLAG          16
# define EOF_FLAG           32
# define FIRST_FLAG         64

t_list	*lexer(const char *line);

#endif
