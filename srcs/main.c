#include"../inc/minishell_c.h"
int main(int ac, char **av, char **envp)
{
    (void)ac;
    //execve("bin/bash", av, envp);
    command_main(++av,envp);
    return 0;
}