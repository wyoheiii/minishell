#include "minishell_c.h"
bool    check_n(char *arg)
{
    size_t i;
    i = 1;
    if(arg[0] != '-')
        return (false);
    while(arg[i] != '\0')
    {
        if(arg[i] != 'n')
            return (false);
        i++;
    }
    return (true);
}
size_t   check_option(char **arg,bool  *option_flag)
{
    size_t i;

    i = 1;
    while(arg[i] != NULL)
    {
        if(!check_n(arg[i]))
        {
            return (i);
        }
        *option_flag = true;
        i++;
    }
    return (i);
}

int my_echo(char **arg)
{
    bool option_flag;
    size_t i;
    i = 1;
    if(arg[i] == NULL)
        write(1,"\n",1);
    else
    {
        option_flag = false;
        i = check_option(arg, &option_flag);
        while(arg[i] != NULL) 
        {
            ft_putstr_fd(arg[i], 1);
            if (arg[i + 1] != NULL )
                write(1," ",1);
            i++;
        }
        if(!option_flag)
            write(1,"\n",1);
    }
    g_status = 0;
    return (0);
}
