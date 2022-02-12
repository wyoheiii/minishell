/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyohei <wyohei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 18:17:29 by wyohei            #+#    #+#             */
/*   Updated: 2022/02/12 18:17:30 by wyohei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_redirect.h"


void heredoc_child(int pfd[2], char *str)
{
    char *line;
    my_close(pfd[0]);
    //printf("str  ;%s\n",str);

    while(1)
    {
        heredoc_sig();
        line = readline("> ");
        if(line == NULL)
            break;
        //printf("%s\n",line);
        if(ft_strncmp(line, str, ft_strlen(str) + 1) == 0)
        {
            break;
        }
        ft_putendl_fd(line,pfd[1]);
        free(line);
    }
    free(line);
    //printf("break sita\n");
    my_close(pfd[1]);
    exit(0);
}
int heredoc_waitpid(pid_t pid,int *status,int option)
{
    if(waitpid(pid, status, option) < 0)
    {
        exit_error("waitpid");
        //exit(1);
    }
    if(*status)
    {
        g_status = WEXITSTATUS(status);
        return (1);
    }
    return (0);
}
int my_heredoc(t_redirect *redirect)
{
    pid_t pid;
    int pfd[2];
    int status;
    int ret;
    ret = 0;
    my_pipe(pfd);

    pid = my_fork();
    if(pid == 0)
        heredoc_child(pfd,redirect->filename);
    else
        ret = heredoc_waitpid(pid,&status,0);
    if(ret)
    {
        my_close(pfd[1]);
        my_close(pfd[0]);
        return(ret);
    }
    my_close(pfd[1]);
    redirect->fd = pfd[0];
    //printf("a\n");
    return(ret);
}

//void heredoc_set(t_redirect *redirect)
//{
//
//}
bool  set_heredoc(t_parsed *parsed)
{
    t_redirect *red;
    red = parsed->redirect;
    while(parsed != NULL)
    {
        while(red != NULL)
        {
            if(red->state == HERE_DOCUMENT) {
                if(my_heredoc(red) != 0)
                    return(false);
            }
            red = red->next;
        }
        if(parsed->next != NULL)
            red = parsed->next->redirect;
        parsed = parsed->next;

    }
    return(true);
}