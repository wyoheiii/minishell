#include "../inc/minishell_c.h"
bool    check_option(char *command)
{
    if(!ft_strncmp(command, "-n", 3))
        return (true);
    return (false);
}

bool my_echo(char **command)
{
    int option_flag;
    size_t i;
    i = 1; //[1]
    option_flag = false;
    //printf("command[2] %s\n",command[2]);
    if (command[1] == NULL)
    {
        //write(1,"\n",2);
        return 1;
    }
    if(check_option(command[1]))//command[1]
    {
        option_flag = true;
        i++;
    }
    while(command[i] != NULL)
    {
        ft_putstr_fd(command[i], 1);//[1] 
        if (command[i + 1] != NULL )//$やるか?
            write(1," ",1);
        i++;
    }
    if(!option_flag)
        write(1,"\n",2);
    return(true);
}