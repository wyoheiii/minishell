#include "my_redirect.h"
void redirect_error()
{
    //: syntax error near unexpected token `newline'
    ft_putendl_fd("minishell : syntax error near unexpected token `newline'",2);
    exit(1);
}

void redirect_append(t_parsed *parsed)
{
    int fd;
    if(parsed->next != NULL)
    {
        parsed = parsed->next;
        if(parsed->command[0] != NULL)
        {
            //my_close();
            fd = open(parsed->command[0],O_WRONLY|O_APPEND|O_CREAT, 0666);
            if(fd == -1)
            {

                ft_putstr_fd("minishell: ",2);
                ft_putstr_fd(parsed->command[0],2);
                ft_putstr_fd(" :",2);
                ft_putendl_fd(strerror(errno),2);
                exit(1);
            }
            //my_dup2(fd,1);
        }
        else
            redirect_error();
    }
}

void redirect_output(t_parsed *parsed)
{
    //pid_t pid;
    int fd;
    //int fd1;
//    pid = my_fork();
//    if(pid == 0) {
    if (parsed->next != NULL) {
        if (parsed->command[0] != NULL) {
            //my_close(1);
            parsed = parsed->next;
            fd = open(parsed->command[0], O_WRONLY | O_TRUNC | O_CREAT, 0666);
            if (fd == -1) {
                ft_putstr_fd("minishell: ", 2);
                ft_putstr_fd(parsed->command[0], 2);
                ft_putstr_fd(" :", 2);
                ft_putendl_fd(strerror(errno), 2);
                exit(1);
            }
            //fd1 = dup(1);
            my_dup2(fd, 1);
            //close(fd);
            //my_dup2(fd1, 1);
        } else
            redirect_error();
    }
        //exit(0);
    //}
    //int status;
    //waitpid_get_status(pid,&status,0);
}

void redirect_input(t_parsed *parsed)
{
    int fd;
    if(parsed->next != NULL)
    {
        parsed = parsed->next;
        if(parsed->command[0] != NULL)
        {
            //my_close(0);
            fd = open(parsed->command[0],O_RDONLY);
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
}
void select_redirect(t_parsed *parsed)
{
    if(parsed->state == REDIRECT_INPUT)
    {
        redirect_input(parsed);
    }
    if(parsed->state == REDIRECT_OUTPUT)
    {
        redirect_output(parsed);
    }
    if(parsed->state == REDIRECT_APPEND)
    {
        redirect_append(parsed);
    }


}
