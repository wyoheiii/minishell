/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyohei <wyohei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 18:16:17 by wyohei            #+#    #+#             */
/*   Updated: 2022/02/12 18:16:18 by wyohei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_c.h"
//=の一個前までを入れる
//void env_pwd_set(t_envlist **lst,char  *pwd)
//{
//}
void    env_init(char **env, t_envlist **envlst) {
    size_t i;
    //extern char **env;
    t_envlist *new;

    *envlst = NULL;
//    for (int k = 0; env[k] != NULL; k++){
//        printf(" env;  %s\n",env[k]);
//    }
    if (*env)
        *envlst = env_new(env[0]);
    i = 1;
    while(env[i] != NULL)
    {
        if((env[i][0] == '_' && env[i][1] == '=')|| ft_strncmp(env[i],"OLDPWD",7)==0)
        {
            i++;
            continue ;
        }
        new = env_new(env[i]);
        lstadd_back(envlst, new);
        i++;
    }
    //env_pwd_set
    if (!key_match_check("OLDPWD", *envlst))
    {
        new = env_new("OLDPWD");
        lstadd_back(envlst, new);
    }
    if(!key_match_check("PWD",*envlst))
    {
        char *char_new;
        char *pwd;
        pwd = getcwd(NULL,0);
        if(!pwd) {
            perror("pwd");
            exit(1);
        }
        char_new = ft_strjoin("PWD=",pwd);
        //printf("char new   : %s\n",char_new);
        free(pwd);
        new = env_new(char_new);
        lstadd_back(envlst,new);
    }
}
