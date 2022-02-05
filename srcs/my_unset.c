#include "minishell_c.h"
//bash-3.2$ unset AAA=
//bash: unset: `AAA=': not a valid identifier
void lst_unset(char *arg, t_envlist **lst)
{
    t_envlist *top;
    t_envlist *prev;
    size_t size; 
    size = ft_strlen(arg);
    if(ft_strncmp(arg,(*lst)->key, size + 1) == 0)
    {
        top = (*lst)->next;
        env_delone(*lst);
        *lst = top;
    }
    else
    {
        top = *lst;
        while(*lst != NULL)
        {
            if(ft_strncmp(arg,(*lst)->key, size + 1) == 0)
            {
                prev->next = (*lst)->next;
                env_delone(*lst);
                break;
            }
            prev = *lst;
            *lst = (*lst)->next;
        }
        *lst = top;
    }
}
void unset_error(char *error)
{
    //printf("minishell: unset: `%s': not a valid identifier\n", args[i]);
    ft_putstr_fd("minishell: unset: `",2);
    ft_putstr_fd(error,2);
    ft_putstr_fd("': not a valid identifier\n",2);
    g_status = 1;
}
int my_unset(char **args, t_envlist **lst)
{
    size_t i;
    int error_flag;
    int ret_flag;
    ret_flag = 0;
    if(args[1] != NULL)
    {
        i = 1;
        error_flag = 0;
        while(args[i])
        {
            if(!char_check(args[i]))
            {
                error_flag = 1;
                ret_flag = 1;
            }
            else
                lst_unset(args[i], lst);
            if (error_flag)
                unset_error(args[i]);
            error_flag = 0;
            i++;
        }
        if(!ret_flag)
            g_status = 0;
    }
    return (0);
}