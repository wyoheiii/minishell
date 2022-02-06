#include "my_redirect.h"
void redirect_error()
{
    //: syntax error near unexpected token `newline'
    ft_putendl_fd("minishell : syntax error near unexpected token `newline'",2);
    exit(1);
}

void redirect_append(t_redirect *redirect)
{
    int fd;
    if(redirect->filename != NULL)
    {
        //my_close();
        fd = open(redirect->filename, O_WRONLY | O_APPEND | O_CREAT, 0666);
        if(fd == -1)
        {

            ft_putstr_fd("minishell: ",2);
            ft_putstr_fd(redirect->filename, 2);
            ft_putstr_fd(" :",2);
            ft_putendl_fd(strerror(errno),2);
            exit(1);
        }
        //my_dup2(fd,1);
    }
    else
        redirect_error();
}

void redirect_output(t_redirect *redirect)
{
    //pid_t pid;
    int fd;
    if(redirect->filename != NULL) {
        fd = open(redirect->filename, O_WRONLY | O_TRUNC | O_CREAT, 0666);
        if (fd == -1) {
            ft_putstr_fd("minishell: ", 2);
            ft_putstr_fd(redirect->filename, 2);
            ft_putstr_fd(" :", 2);
            ft_putendl_fd(strerror(errno), 2);
            exit(1);
        }
        my_dup2(fd, 1);
        my_close(fd);
    }
    else
        redirect_error();
}

void redirect_input(t_redirect *redirect)
{
    int fd;
    if(redirect->filename != NULL)
    {
        //my_close(0);
        fd = open(redirect->filename,O_RDONLY);
        if(fd == -1)
        {
            ft_putendl_fd("testerror",2);
            exit(1);
        }
        my_dup2(fd,0);
    }
    else
        redirect_error();
}
void select_redirect(t_redirect *redirect)
{
    if(redirect->state == REDIRECT_INPUT)
    {
        redirect_input(redirect);
    }
    if(redirect->state == REDIRECT_OUTPUT)
    {
        redirect_output(redirect);
    }
    if(redirect->state == REDIRECT_APPEND)
    {
        redirect_append(redirect);
    }


}
