#include "my_redirect.h"


void heredoc_child(int pfd[2], char *str)
{
    char *line;
    my_close(pfd[0]);
    //printf("str  ;%s\n",str);
    heredoc_sig();
    while(1)
    {
        line = readline("> ");
        if(line == NULL)
            continue;
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

void my_heredoc(t_redirect *redirect)
{
    pid_t pid;
    int pfd[2];
    int status;
    my_pipe(pfd);
    //int dup = my_dup(0);

    pid = my_fork();
    if(pid == 0)
        heredoc_child(pfd,redirect->filename);
    else
        waitpid_get_status(pid,&status,0);
    my_close(pfd[1]);
    redirect->fd = pfd[0];
}

//void heredoc_set(t_redirect *redirect)
//{
//
//}
void set_heredoc(t_parsed *parsed)
{
    t_redirect *red;
    red = parsed->redirect;
    while(parsed != NULL)
    {
        while(red != NULL)
        {
            if(red->state == HERE_DOCUMENT) {
                my_heredoc(red);
            }
            red = red->next;
        }
        if(parsed->next != NULL)
            red = parsed->next->redirect;
        parsed = parsed->next;

    }

}