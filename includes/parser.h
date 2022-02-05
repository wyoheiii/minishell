#ifndef PARSER_H
# define PARSER_H

# include <stdbool.h>
# include <stdlib.h>

# include "libft.h"
# include "delimiter.h"
# include "redirect_list.h"
# include "utils.h"

typedef struct s_parsed
{
	char				**command;
	int					state;
	struct s_redirect	*redirect;
	struct s_parsed		*next;
}	t_parsed;

t_parsed	*parser(t_list **token_list);
void		free_parsed(t_parsed **parsed);

#endif
