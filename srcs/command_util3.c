#include "minishell_c.h"

void    check_period(t_parsed *parsed)
{
    if (parsed != NULL)
    {
        if (parsed->command[0] != NULL)
        {
            if (ft_strncmp(parsed->command[0], "..", 3) == 0 || \
                ft_strncmp(parsed->command[0], ".", 2) == 0)
            {
                ft_putstr_fd("minishell: ", 2);
                ft_putstr_fd(parsed->command[0], 2);
                ft_putstr_fd(": ", 2);
                ft_putendl_fd("command not found", 2);
                exit(127);
            }
        }
    }
}

