/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyohei <wyohei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 18:17:03 by wyohei            #+#    #+#             */
/*   Updated: 2022/02/12 18:17:04 by wyohei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_c.h"
// bash-3.2$ export _=AA
// bash-3.2$ echo $?
// 0
// bash-3.2$ export _=AA
// bash-3.2$ echo $_
// _
int my_env(t_envlist *envlst)
{
    while(envlst != NULL)
    {
        if(envlst->key[0] == '_' && envlst->key[1] == '\0')
        {
            //_=やらなくていいかも
            //printf("wakaran\n");
            continue;
            //_=/usr/bin/env
        }
        else if(envlst->value != NULL && envlst->value[0] != '\0')
                printf("%s=%s\n", envlst->key, envlst->value);
        envlst = envlst->next;
    }
    g_status = 0;
    return(0);
}
