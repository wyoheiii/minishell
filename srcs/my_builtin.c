/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyohei <wyohei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 16:01:01 by wyohei            #+#    #+#             */
/*   Updated: 2022/02/12 17:30:07 by wyohei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_c.h"
int    return_builtin(char **command, t_envlist **envlst, t_god god)
{
    int ret;

    ret = 0;
    if(command[0] == NULL)
        return (0);
    if(!ft_strncmp(command[0], "echo", 5))
        ret = my_echo(command);
    else if(!ft_strncmp(command[0], "cd", 3))
        ret = my_cd(command, envlst);
    else if(!ft_strncmp(command[0], "pwd", 4))
        ret = my_pwd(god.pwd);
    else if(!ft_strncmp(command[0], "export", 7))
        ret = my_export(command, envlst);
    else if(!ft_strncmp(command[0], "unset",6))
        ret = my_unset(command, envlst);
    else if(!ft_strncmp(command[0], "env",4))
        ret = my_env(*envlst);
    else if(!ft_strncmp(command[0], "exit",5))
        ret = my_exit(command);
    return (ret);
}

bool    builtin_select(char **command)
{
    if(command[0] == NULL)
        return(true);
    if(!ft_strncmp(command[0], "echo",5))
        return(true);
    else if(!ft_strncmp(command[0], "cd", 3))
        return(true);
    else if(!ft_strncmp(command[0], "pwd",4))
        return(true);
    else if(!ft_strncmp(command[0], "export",7))
        return(true);
    else if(!ft_strncmp(command[0], "unset",6))
        return(true);
    else if(!ft_strncmp(command[0], "env",4))
        return(true);
    else if(!ft_strncmp(command[0], "exit",5))
        return(true);
    return (false);
}

int single_builtin(t_god god,t_envlist **lst)
{
    int fd1;
    int fd2;
    int fd3;
    int ret;

    fd1 = my_dup(0);
    fd2 = my_dup(1);
    fd3 = my_dup(2);
    if(redirect_check(god.parsed))
        select_redirect(god.parsed->redirect);
    ret = return_builtin(god.parsed->command, lst,god);
    my_dup2(fd1,0);
    my_dup2(fd2,1);
    my_dup2(fd3,2);
    my_close(fd1);
    my_close(fd2);
    my_close(fd3);
    return(ret);
}

int single_command(t_god god,t_envlist **lst)
{
    pid_t pid;
    char *path;
    int status;
    char **env_array;

    env_array = lst_in_array(*lst);
    if(builtin_select(god.parsed->command))
        return (single_builtin(god,lst));
    pid = my_fork();
    if (pid == 0)
    {
        if(redirect_check(god.parsed))
            select_redirect(god.parsed->redirect);
        path = get_path(*lst,god.parsed->command[0]);
        if(execve(path, god.parsed->command, env_array) == -1)
            exec_error(path,*lst);
        free(path);
    }
    else
        waitpid_get_status(pid,&status,0);
    free_array(env_array);
    return (0);
}