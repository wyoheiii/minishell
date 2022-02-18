#include "minishell_c.h"

t_pwd *pwd_new(char *dir)
{
    t_pwd *new;

    new = malloc(sizeof(t_pwd));
    if(new == NULL)
        exit_error("malloc");
    new->dir_name = dir;
    new->next = NULL;
    new->prev = NULL;
    return(new);
}

t_pwd *pwd_last(t_pwd *pwd)
{
    if(pwd == NULL)
        return (NULL);
    while(pwd->next != NULL)
        pwd= pwd->next;
    return (pwd);
}

void pwd_add_back(t_pwd **top, t_pwd *new)
{
    t_pwd *tmp;

    if (top == NULL)
        return ;
    if(*top != NULL)
    {
        tmp = pwd_last(*top);
        tmp->next = new;
        new->prev = tmp;
    }
    else
        *top = new;
}

void	pwd_lstclear(t_pwd	**lst)
{
    t_pwd	*tmp;

    if (lst == NULL)
        return ;
    while (*lst != NULL)
    {
        tmp = (*lst)->next;
        free((*lst)->dir_name);
        free(*lst);
        *lst = tmp;
    }
    *lst = NULL;
}