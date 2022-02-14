#ifndef MINISHELL_H
# define MINISHELL_H
typedef struct s_envlist
{
    char *key;
    char *value;
    struct s_envlist *next;
} t_envlist;
#include "minishell_c.h"

int g_status;
#endif // !
