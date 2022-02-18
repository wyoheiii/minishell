/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyohei <wyohei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 18:16:55 by wyohei            #+#    #+#             */
/*   Updated: 2022/02/15 00:21:53 by wyohei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_c.h"

int	cd_error(char *error)
{
	if (error == NULL)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		g_status = 1;
		return (0);
	}
	else
	{
		g_status = 1;
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(error, 2);
        ft_putendl_fd(strerror(errno),2);
		return (0);
	}
}

int nosuch_err(char *err)
{
    g_status = 1;
    ft_putstr_fd("minishell : cd : ", 2);
    ft_putstr_fd(err, 2);
    ft_putstr_fd(":", 2);
    ft_putendl_fd(": No such file or directory", 2);
    return (0);
}

char *get_cd_path(char *command, t_envlist **lst)
{
    char *path;

    if (command == NULL)
    {
        path = search_env_key_("HOME", *lst);
        if (path == NULL)
            return (NULL);
        return(my_strdup(path));
    }
    return (my_strdup(command));
}
int cd_err(int errr, char *err)
{
    errno = errr;
    g_status = 1;
    ft_putstr_fd("minishell : cd :", 2);
    ft_putstr_fd(err, 2);
    ft_putstr_fd(":", 2);
    ft_putendl_fd(strerror(errno), 2);
    return (0);
}
void set_pwd(char *pwd, char *value, t_envlist **lst)
{
    char	*keyvalue;
    if (key_match_check(pwd, *lst))
    {
        keyvalue = strjoinjoin(pwd, "=", value);
        dup_value(keyvalue, lst);
        free(keyvalue);
    }
}
bool end_slash(char *path)
{
    size_t i;
    i = ft_strlen(path);
    if(path[i - 1] == '/')
        return (true);
    return (false);
}
void new_pwd_oldpwd(t_god *god,t_envlist **lst, char *path)
{
    char *new;

    if(god->oldpwd != NULL)
        free(god->oldpwd);
    god->oldpwd = my_strdup(god->pwd);
    if (!end_slash(god->pwd))
        new = strjoinjoin(god->pwd, "/", path);
    else
        new = ft_strjoin(god->pwd, path);
    if (new == NULL)
        exit_error("malloc");
    set_pwd("PWD", new, lst);
    set_pwd("OLDPWD", god->pwd, lst);
    if(god->pwd != NULL)
        free(god->pwd);
    god->pwd = my_strdup(new);
    free(new);
}
int ret_err_period(char *path,t_god *god, t_envlist **lst, bool flag)
{
    ft_putstr_fd("cd :error retrieving current directory: ", 2);
    ft_putstr_fd("getcwd: cannot access parent directories: ",2);
    ft_putendl_fd("No such file or directory", 2);
    new_pwd_oldpwd(god, lst, path);
    if(flag)
        free(path);
    g_status = 0;
//    printf("god  pwd  :%s\n",god->pwd);
//    printf("lst pwd  ;%s\n", search_env_key_("PWD",*lst));
//    printf("god  oldpwd  :%s\n",god->oldpwd);
//    printf("lst oldpwd  ;%s\n", search_env_key_("OLDPWD",*lst));
    return(0);
}

void    pwd_splitarray_to_list(char *path, t_pwd **pwd)
{
    char **split;
    int i;

    i = 0;
    //printf("kokomade\n");
    split = my_split(path, '/');
    while(split[i] != NULL)
    {
        pwd_add_back(pwd, pwd_new(my_strdup(split[i])));
        i++;
    }
    //printf("kokomade\n");
    split_free(split);
}

void del_current(t_pwd **pwd, t_pwd **top)
{
    t_pwd *tmp;
    tmp = *pwd;
    if(*pwd == NULL)
        return ;
    //tmp = *pwd;
    if((*pwd)->prev == NULL)
    {
        (*pwd) = (*pwd)->next;
        if(*pwd)
            (*pwd)->prev = NULL;
        *top = *pwd;
        free(tmp->dir_name);
        free(tmp);
        return ;
    }
    else
    {
        (*pwd)->prev->next = (*pwd)->next;
        if((*pwd)->next != NULL)
            (*pwd)->next->prev = (*pwd)->prev;
        // free(tmp->dir_name);
        // free(tmp);
    }
}
void  del_period(t_pwd **pwd)
{
    t_pwd *top;
    top = *pwd;

    while(*pwd != NULL)
    {
        if (*pwd != NULL && ft_strncmp((*pwd)->dir_name, "..", 3) == 0)
        {
            if((*pwd)->prev != NULL)
                del_current(&(*pwd)->prev,&top);
            del_current(pwd,&top);
            if(*pwd)
                *pwd = (*pwd)->next;
            continue;
        }
        if(*pwd != NULL && (ft_strncmp((*pwd)->dir_name, ".", 2) == 0))
        {
            del_current(pwd, &top);
            if(*pwd)
                *pwd = (*pwd)->next;
            continue;
        }
        if(*pwd)
            *pwd = (*pwd)->next;
    }
    *pwd = top;
}
char *join_path(t_pwd *pwd)
{
    char *path;
    char *tmp;
    path = NULL;
    if(pwd)
    {
        path = ft_strjoin("/", pwd->dir_name);
        if(path == NULL)
            exit_error("malloc");
        pwd = pwd->next;
    }
    while(pwd != NULL)
    {
        tmp = strjoinjoin(path,"/",pwd->dir_name);
        if(tmp == NULL)
            exit_error("malloc");
        free(path);
        path = tmp;
        pwd = pwd->next;
    }
    return(path);
}
char *create_path(char *path, t_god *god)
{
    char *new_path;
    t_pwd *pwd;

    pwd = NULL;
    new_path = strjoinjoin(god->pwd,"/",path);
    if(new_path == NULL)
        exit_error("malloc");
    //printf("kokomade\n");
    pwd_splitarray_to_list(new_path, &pwd);
    //printf("kokomade\n");
    del_period(&pwd);
    free(new_path);
    new_path = join_path(pwd);
    //printf("kokomade\n");
    pwd_lstclear(&pwd);
    return(new_path);
}
bool current_dir_check(void)
{
    struct stat sh;
    char *cwd;
    cwd = getcwd(NULL, 0);
    if(lstat(cwd,&sh) == 0)
    {
        free(cwd);
        return (true);
    }
    return (false);
}
void set_new_pwd(t_god *god, char *path,t_envlist **lst,char *err_path)
{
    char *new_path;
    t_pwd *pwd;
    pwd = NULL;
    if(!current_dir_check())
    {
        ret_err_period(err_path, god, lst,false);
        return ;
    }
    if(path != NULL && ft_strncmp(path, "/",2) != 0) {
        pwd_splitarray_to_list(path, &pwd);
        del_period(&pwd);
    }
    new_path = join_path(pwd);
    if(new_path == NULL)
        new_path = my_strdup("/");
    //free(path);
    //printf("kokomade\n");
    if(god->oldpwd != NULL)
        free(god->oldpwd);
    god->oldpwd = my_strdup(god->pwd);
    //pwd_splitarray_to_list(path, &pwd);
    set_pwd("PWD",new_path, lst);
    set_pwd("OLDPWD", god->pwd, lst);
    if(god->pwd != NULL)
        free(god->pwd);
    god->pwd = my_strdup(new_path);
    pwd_lstclear(&pwd);
    g_status = 0;
}
int	my_cd(char **command, t_envlist **lst, t_god *god)
{
	char	*path;
    char    *cwd;
    char    *new_path;
    if (command != NULL && command[1] != NULL && command[1][0] == '~')
        return(0);
    path = get_cd_path(command[1], lst);
    if (path == NULL && key_match_check( "HOME",  *lst))
        return (cd_err(2, " "));
    if (path == NULL && !key_match_check("HOME",*lst))
        return(cd_error(NULL));
    cwd = getcwd(NULL, 0);
    if((ft_strncmp(path,".", 2) == 0 || ft_strncmp(path,"./", 3) == 0) && cwd == NULL)
        return(ret_err_period(path, god, lst,true));
    //printf("path  ;%s\n",path);
    //printf("kokomade\n");
    if(path && path[0] == '/')
        new_path = my_strdup(path);
    else
        new_path = create_path(path, god);
    //printf("kokomade\n");
    if (chdir(path) != 0)
    {
        //printf("chdir sippai kokomade\n");
        cd_error(path);}
    else
        set_new_pwd(god, new_path, lst, path);
    //printf("path   ;%s\n",path);
    //printf("new path   ;%s\n",new_path);
    free(new_path);
    free(cwd);
    free(path);
	return (0);
}
