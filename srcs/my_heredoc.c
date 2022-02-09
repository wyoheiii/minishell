#include "my_redirect.h"
//void heredoc_child(int pfd[2], t_redirect *redirect)
//{
//    char *line;
//    while(1)
//    {
//        line = readline();
//    }
//}
//
//void my_heredoc(t_redirect *redirect)
//{
//    pid_t pid;
//    int pfd[2];
//    int status;
//    my_pipe(pfd);
//    pid = my_fork();
//    if(pid == 0)
//        heredoc_child(pfd,redirect);
//    else
//        waitpid_get_status(pid,&status,0);
//
//}