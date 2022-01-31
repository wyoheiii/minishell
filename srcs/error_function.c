#include "minishell_c.h"
// pipe  waitpid
void exit_error(char *error)
{
    ft_putstr_fd(error,2);
    ft_putendl_fd(" error",2);
    exit(1);
}

void my_dup2(int old_fd, int newfd)
{
    if(dup2(old_fd, newfd) == -1)
    {
        exit_error("dup2");
        exit(1);
    }
}
void my_close(int fd)
{
    if(close(fd) == -1)
    {
        exit_error("close");
        exit(1);
    }
}
void	*my_malloc(size_t size)
{
    void	*ret;

    ret = malloc(size);
    if (!ret)
    {
        exit_error("malloc");
        exit(1);
    }
    return (ret);
}
pid_t my_fork(void)
{
    pid_t ret;
    ret = fork();
    if(ret == -1)
    {
        exit_error("fork");
        exit(1);
    }
    return(ret);
}