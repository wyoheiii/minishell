/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyohei <wyohei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 18:17:32 by wyohei            #+#    #+#             */
/*   Updated: 2022/02/12 18:17:33 by wyohei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_c.h"
int my_pwd(char *pwd)
{
    char *dir;
    (void)pwd;
    dir = getcwd((char *)NULL, 0);
   // printf("pwd :%s\n",pwd);
    if(!dir)
        perror("getcwd");
    else
    {
        printf("%s\n", dir);
        free(dir);
    }
    g_status = 0;
    return(0);
    //return(dir == NULL ? EXIT_FAILURE : EXIT_SUCCESS);
}