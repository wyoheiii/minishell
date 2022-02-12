/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyohei <wyohei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 18:16:55 by wyohei            #+#    #+#             */
/*   Updated: 2022/02/12 18:16:56 by wyohei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_c.h"
//失敗が1成功が0
//bash: cd: lv03: No such file or directory
// OLD PWD更新
// rm でカレントディレクトリ消した後にｃｄ．とか
int cd_error(char *error)
{
    if(error == NULL)
    {
        ft_putstr_fd("minishell: cd: HOME not set\n",2);
        g_status = 1;
        return (0);
    }
    else
    {
        g_status = 1;
        ft_putstr_fd("minishell: cd: ", 2);
        ft_putstr_fd(error, 2);
        //ft_putstr_fd(, 2);
        //ft_putstr_fd(, 2);
        return (0);
    }

}
// cd -- zissou
//mkdir dir cd DIR pwd /DIR 大文字になっとる
//mkdir dir  cd dir rmdir . cd .
//cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory
//case: mkdir -p a/b/c\n cd a/b/c\n rm -rf ../../b\n cd ./\n pwd\n cd ../\n pwd\n cd .////./\n pwd\nexit
void set_pwd(t_envlist **lst,char *pwd)
{
    char *key_value;
    char *cwd;

    if(key_match_check(pwd,*lst))
    {
        cwd = getcwd(NULL, 0);
        //printf("cwd   ;%s\n",cwd);
        if(cwd == NULL)
        {
            perror("cwd");
            exit(1);
        }
        key_value = strjoinjoin(pwd,"=",cwd);
        //printf("pwd  ;%s\n",key_value);
        dup_value(key_value, lst);
        free(cwd);
    }
}
int my_cd(char **command, t_envlist **lst)
{
    char *path;
    char *error;

    set_pwd(lst, "OLDPWD");
    if(command[1] == NULL)
    {
        path = search_env_key_("HOME", *lst);
        if(path == NULL)
            return (cd_error(NULL));
        if(chdir(path) != 0)
            perror("chdir");
    }
    else
    {
        if(chdir(command[1]) != 0)
        {
            error = ft_strjoin("minishell: cd: ",command[1]);
            if(error == NULL)
                exit_error("malloc");
            g_status = 1;
            perror(error);
            free(error);
            return (0);
        }
    }
    set_pwd(lst, "PWD");
    g_status = 0;
    return(0);
}