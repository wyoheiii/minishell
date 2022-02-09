#ifndef EXPAND_STRUCT_H
# define EXPAND_STRUCT_H

# include <stdlib.h>
# include "libft.h"

# define NONE	0
# define SINGLE 1
# define DOUBLE 2
# define DELIMITER " \t\n"

typedef struct s_expand
{
	char			*argv;
	int				flag;
	size_t			index;
	size_t			checked;
	struct s_expand	*next;
}	t_expand;

t_expand	*convert_list(char **command);
t_expand	*expand_new(char *argv);
void		expand_add_back(t_expand **head, t_expand *new);
void		free_expand(t_expand **expand);

#endif
