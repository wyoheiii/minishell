#include "minishell_c.h"
// pipe  waitpid
void my_pipe(int *pipefd)
{
    if(pipe(pipefd) == -1)
    {
        exit_error("pipe");
        exit(1);
    }
}

void waitpid_get_status(pid_t pid, int *status,int option)
{
    if(waitpid(pid, status, option) < 0)
    {
        exit_error("waitpid");
        exit(1);
    }
    if(WIFEXITED(*status))
        g_status = WEXITSTATUS(*status);
}
