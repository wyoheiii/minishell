#ifndef PARSER_H
# define PARSER_H

# include <stdbool.h>
# include <stdlib.h>

# include "libft.h"
# include "delimiter.h"
# include "utils.h"

# define NONE 			    0
# define PIPE 			    1
# define REDIRECT_INPUT	    2
# define REDIRECT_OUTPUT	3
# define REDIRECT_APPEND	4
# define HERE_DOCUMENT	    5

typedef struct s_parsed
{
	char			**command;
	int				state;
	struct s_parsed	*next;
}	t_parsed;

t_parsed	*parser(t_list **token_list);

#endif
