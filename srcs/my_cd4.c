/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_cd4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyohei <wyohei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 15:15:56 by wyohei            #+#    #+#             */
/*   Updated: 2022/02/21 15:44:12 by wyohei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_c.h"

void set_new_pwd2(t_god *god, char *path,t_envlist **lst)
{
	char *new_path;
    t_pwd *pwd;
    pwd = NULL;

	if(path != NULL && ft_strncmp(path, "/",2) != 0)
    {
        pwd_splitarray_to_list(path, &pwd);
        del_period(&pwd);
    }
    new_path = join_path(pwd);
    if(new_path == NULL)
        new_path = my_strdup("/");
    if(god->oldpwd != NULL)
        free(god->oldpwd);
    god->oldpwd = my_strdup(god->pwd);
    set_pwd("PWD",new_path, lst);
    set_pwd("OLDPWD", god->pwd, lst);
    if(god->pwd != NULL)
        free(god->pwd);
    god->pwd = my_strdup(new_path);
    pwd_lstclear(&pwd);
	free(new_path);
    g_status = 0;
}

void set_new_pwd(t_god *god, char *path,t_envlist **lst,char *err_path)
{

    if(!current_dir_check())
    {
        ret_err_period(err_path, god, lst, false);
        return ;
    }
	set_new_pwd2(god,path,lst);
}