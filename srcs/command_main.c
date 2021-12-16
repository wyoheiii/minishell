#include "../inc/minishell_c.h"

size_t  command_size(char **command)
{
    size_t i;
    i= 0;
    while(command[i] != NULL)
        i++;
    return(i);
}
bool test_echo(char **command)
{
    size_t i;
    size_t  size;
    i = 0;
    if(check_option(command));
    size = command_size(command);
    while( i < size)
    {
        ft_putendl_fd(command[],1);//[1]
    }

    return(true);
}

bool    builtin_select(char **command)
{
    if(!ft_strncmp(command[1], "echo",5))
        return(test_echo(command));
    if(!ft_strncmp(command[1], "cd",3))
        return(true);
    if(!ft_strncmp(command[1], "pwd",4))
        return(true);
    if(!ft_strncmp(command[1], "export",7))
        return(true);
    if(!ft_strncmp(command[1], "unset",6))
        return(true);
    if(!ft_strncmp(command[1], "env",4))
        return(true);
    if(!ft_strncmp(command[1], "exit",5))
        return(true);
    return (false);
}
void command_main(char **av,char **envp)
{
    //int pid ;
    char *command ;//=  "cat";
    const char *add_path = "/bin/";
    //char *tmp;

    //pid = fork();
    //if(pid < 0)
    //{
        //error errono使う
    //}
    //tmp = av[1]; //strdup?
    // if (!tmp)
    //オリジナルのbuiltinが絶対パスできたらどうするか？
    if(builtin_select(av))
        return;
    if(ft_strncmp(av[1], add_path, 4) != 0)//av[0]
        command = ft_strjoin(add_path, av[1]);//av[0]
    //if(command == NULL)
    //     return NULL;
    else
         command = av[1]; //av[0]
    printf("linne::::%s\n",command);
    //printf("envp::%s\n",envp[1]);
    av++; //ここも修正
    execve(command, av, envp);
    if(errno)
    {
        ft_putstr_fd("bash: ",2);
        ft_putstr_fd(command, 2);
        ft_putstr_fd(": ", 2);
        ft_putendl_fd(strerror(errno),2);
        exit(errno);
    }
}