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
static bool exit_atoi2(char *str,int flag, size_t i, size_t *num)
{
    long long max;
    long long one;
    max = (LLONG_MAX) / 10;
    one = (LLONG_MAX) % 10;
    while(str[i] != '\0')
    {
        if(*num > max || (*num == max && ()))
            return(false);
    }
}
bool exit_atoi(char *str, size_t *num)
{
    int flag;
    size_t i;
    //long long ten;
    //long long one;
    i = 0;
    flag = 1;
    if(str[0] == '+' || str[0] == '-')
    {
        if(str[0] != '-')
            flag = -1;
        i++;
    }
    while(str[i] != '\0')
    {
        if(i > 19)
            return (false);
        if((flag == 1 && *num > (size_t)LLONG_MAX) 
        || (flag == -1 && *num  > ((size_t)LLONG_MAX) + 1))
            return (false);
        printf("ret  :%ld\n", *num);
        printf("size_t long  :%ld\n", (size_t)LLONG_MAX) + 1);
        *num = *num * 10 + str[i] - '0';
        i++;
    }
    return (exit_atoi2(str, flag , i, num));
    
}
int my_exit(char **command)
{
    int ret;
    int size;
    size_t num;
    printf("exit\n");
    size = command_size(command);
    ret = 0;
    num = 0;
    if(size == 1)
        return (ret);
    //printf("commmand [1]%d\n",(unsigned char)ft_atoi(command[1]));
    if (check_num(command[1]) && exit_atoi(command[1] , &num))
    {
        printf("ret  :%ld\n",num);
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