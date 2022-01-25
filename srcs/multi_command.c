#include "minishell_c.h"
//int count_pipe(t_parsed *parsed)
//{
//    int ret;
//    ret = 0;
//
//    while(parsed != NULL)
//    {
//        if(parsed->state == PIPE)
//            ret++;
//        parsed = parsed->next;
//    }
//    return (ret);
//}
//
//int multi_command(t_parsed *parsed, t_envlist **lst, char **env_array)
//{
//    int pipe_count;
//    int **pipe_fd;
//    int i;
//    pid_t pid;
//    pipe_count = count_pipe(parsed);
//    pipe_fd = malloc(sizeof(int *) * (pipe_count + 1));
//    if(pipe_fd == NULL)
//        exit(1);
//    *pipe_fd = malloc(sizeof(int) * 2);
//    if(*pipe_fd == NULL)
//        exit(1);
//    if(pipe_count == 0)
//    {
//        //return(single_command);
//    }
//    i = 0;
//    while(parsed != NULL)
//    {
//        pid = fork();
//        if(pid == 0)
//        {
//            if(i == 0)
//            {
//                dup2(pipe_fd[i][1],1);
//                close(pipe_fd[i][0]);
//                close(pipe_fd[i][1]);
//            }
//            else if (i == pipe_count)
//            {
//                dup2(pipe_fd[i - 1][0], 0);
//                close(pipe_fd[i - 1][0]);
//                close(pipe_fd[i - 1][1]);
//            }
//            else
//            {
//                dup2(pipe_fd[i - 1][0], 0);
//                dup2(pipe_fd[i][1], 1);
//                close(pipe_fd[i - 1][0]);
//                close(pipe_fd[i - 1][1]);
//                close(pipe_fd[i][0]);
//                close(pipe_fd[i][1]);
//            }
//
//        }
//        i++;
//        parsed = parsed->next;
//    }
//}

