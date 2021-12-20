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
            return (false);
        if(flag == -1 && (*num > max || (*num == max && ((str[i] - '0') > one + 1))))
            return (false);
        *num = *num * 10 + str[i] - '0';
        i++;
    }
    printf("ret  :%lld\n", *num);
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
    return (exit_atoi2(str, flag , i, num));
    
}
int my_exit(char **command)
{
    int ret;
    int size;
    long long num;
    printf("exit\n");
    size = command_size(command);
    ret = 0;
    num = 0;
    if(size == 1)
        return (ret);
    //printf("commmand [1]%d\n",(unsigned char)ft_atoi(command[1]));
    if (check_num(command[1]) && exit_atoi(command[1] , &num))
    {
        printf("ret  :%lld\n",num);
        ret = (unsigned char)num;
        return (ret);
    }
    printf("ret  :%d",ret);
    if (size == 2 && check_num(command[1]))
        return(ret);
    if (size > 2 && check_num(command[1]))//ここはbashぬけない
    {
        ret = 1;//std error のほうがいいのか？
        printf("minishell: exit: too many arguments\n");
        return (ret);
    }
    else if(size > 1)
    {
        ret = 255;
        printf("minishell: exit: %s:numeric argument required\n",command[1]);
        return(ret);
    }
    return (ret);// exitのみなら返り値は0;
}//19桁以上の場合はnumeric なんちゃら
//18桁未満の場合はexitできる