/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_export3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyohei <wyohei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 18:17:26 by wyohei            #+#    #+#             */
/*   Updated: 2022/02/12 18:17:27 by wyohei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_c.h"
int	isenv(int	c)
{
    if ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z')
        || (c >= 'a' && c <= 'z') || c == '_' )
        return (1);
    return (0);
}

int is_alpha_(int c)
{
    if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_')
        return (1);
    return (0);
}

void dup_value(char *arg, t_envlist **lst)
{
    size_t key_size;
    char *tmp;
    char *key;
    t_envlist *top;

    key = env_get_key(arg);
    key_size = ft_strlen(key);
    top = *lst;
    while(*lst != NULL)
    {
        if(ft_strncmp(key,(*lst)->key, key_size + 1) == 0)
        {
            //printf("key  :%s",key);
            tmp = env_get_value(arg);
            //printf("value ;%s\n",tmp);
            free((*lst)->value);
            (*lst)->value = tmp;
            *lst = top;
            return ;
        }
        *lst = (*lst)->next;
    }
}

void join_value(char *arg, t_envlist **lst)
{
    size_t key_size;
    char *value;
    char *key;
    t_envlist *top;

    key = env_get_key(arg);
    value = env_get_value(arg);
    key_size = ft_strlen(key);
    top = *lst;
    while(*lst != NULL)
    {
        if(ft_strncmp(key,(*lst)->key, key_size + 1) == 0)
        {
            if ((*lst)->value == NULL)
                (*lst)->value =  value;
            else
                (*lst)->value = my_strjoin(&(*lst)->value, &value);
            *lst = top;
            return ;
        }
        *lst = (*lst)->next;
    }
}

bool set_key_value(char *arg, t_envlist **lst)
{

    int join_flag;
    t_envlist *new;

    join_flag = 0;
    if(check_arg(arg, &join_flag))
    {
        if (key_match_check(arg, *lst))
        {
            if(ft_strchr(arg,'=') == NULL)
                return(true);
            if(join_flag)
                join_value(arg, lst);
            else
                dup_value(arg, lst);
        }
        else
        {
            new = env_new(arg);
            lstadd_back(lst,new);
        }
        return(true);
    }
    return(false);
}
