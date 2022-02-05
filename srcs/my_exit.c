#include "minishell_c.h"
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
    if(command[0] == '+' || command[0] == '-')
        i++;
    while(command[i] != '\0')
    {
        if(!ft_isdigit(command[i]))
            return(false);
        i++;
    }
    return (true);
}
static bool exit_atoi2(char *str,int flag, size_t i, long long *num)
{
    long long max;
    long long one;
    max = (LLONG_MAX) / 10;
    one = (LLONG_MAX) % 10;
    while(str[i] != '\0')
    {
        if(i > 19)
            return (false);
        if(flag == 1 && (*num > max || (*num == max && (str[i] - '0' > one))))
            return(false);
        if(flag == -1 &&(*num > max || (*num == max && ((str[i] - '0') > one + 1))))
            return(false);
        *num = *num * 10 + str[i] - '0';
        i++;
    }
    *num =  flag * ((long long)*num);
    return (true);
}
bool exit_atoi(char *str, long long *num)
{
    int flag;
    size_t i;
    i = 0;
    flag = 1;
    if(str[0] == '+' || str[0] == '-')
    {
        if(str[0] == '-')
            flag = -1;
        i++;
    }
    while(str[i] == '0' && str[i] != '\0')
    {
        i++;
    }
    return (exit_atoi2(str, flag , i, num));
    
}
int exit_error_c(char *error)
{
    if(error == NULL)
    {
        g_status = 1;
        ft_putstr_fd("minishell: exit: too many arguments\n",2);
        return (0);
    }
    else
    {
        g_status = 255;
        ft_putstr_fd("minishell: exit: ",2);
        ft_putstr_fd(error,2);
        ft_putstr_fd("numeric argument required\n",2);
        return(EXIT);
    }
}
int my_exit(char **command)
{
    int ret;
    int size;
    long long num;
    //printf("exit\n");
    size = command_size(command);
    ret = 0;
    num = 0;
    if(size == 1)
    {
        g_status = 0;
        return (EXIT);
    }
    if (check_num(command[1]) && exit_atoi(command[1] , &num))
    {
        //printf("ret  :%lld\n",num);
        g_status = (unsigned char)num;
        return (EXIT);
    }
    //printf("ret  :%d",ret);
    if (size == 2 && check_num(command[1]))
        return(EXIT);
    if (size > 2 && check_num(command[1]))//ここはbashぬけない
        return (exit_error_c(NULL));
    else if(size > 1)
        return(exit_error_c(command[1]));
    g_status = 0;
    return (EXIT);
}