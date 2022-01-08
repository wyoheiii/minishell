#ifndef EXPANSION_H
# define EXPANSION_H

# include "parser.h"
# include "expand_param.h"

# define NONE	0
# define SINGLE 1
# define DOUBLE 2

bool	expansion(t_parsed *parsed);

#endif
