#include "../inc/minishell_c.h"
int command_size(char **arg)
{
    int i;
    i = 0;
    while(arg[i] != NULL)
        i++;
    return (i);
}
bool    check_num(char *command)
{
    size_t i;
    i = 0;
    while(command[i] != '\0')
    {
        if(!ft_isdigit(command[i]))
            return(false);
        i++;
    }
    return (true);
}
int my_exit(char **command)
{
    int ret;
    int size;
    printf("exit\n");
    size = command_size(command);
    ret = 0;
    if(size == 1)
        return (0);
    //printf("commmand [1]%d\n",(unsigned char)ft_atoi(command[1]));
    else if (size == 2 && check_num(command[1]))
        return((unsigned char)ft_atoi(command[1]));
    else if(size > 2 && check_num(command[1]))//ここはbashぬけない
    {
        ret = 1;//std error のほうがいいのか？
        printf("minishell: exit: too many arguments\n");
    }
    else if(size > 1)
    {
        ret = 255;
        printf("minishell: exit: %s:numeric argument required\n",command[1]);
    }
    return ret;// exitのみなら返り値は0;
}