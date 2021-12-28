#include "../inc/minishell_c.h"
//malloc失敗した時どうfreeするか
int    return_builtin(char **command, t_envlist **envlst)
{
    int ret;
    ret = 0;
    if(!ft_strncmp(command[0], "echo",5))
        ret = my_echo(command);
    else if(!ft_strncmp(command[0], "cd",3))
        ret = my_cd(command);
    else if(!ft_strncmp(command[0], "pwd",4))
        ret = my_pwd();
    else if(!ft_strncmp(command[0], "export",7))
        ret = my_export(command, envlst);
    else if(!ft_strncmp(command[0], "unset",6))
        ret = my_unset(command, envlst);
    else if(!ft_strncmp(command[0], "env",4))
        ret = my_env(*envlst);
    else if(!ft_strncmp(command[0], "exit",5))
        ret = my_exit(command); //構造体でretの値渡したほうがいいかもしれん
    return (ret);
}

bool    builtin_select(char **command)
{
    if(!ft_strncmp(command[0], "echo",5))
        return(true);
    else if(!ft_strncmp(command[0], "cd",3))
        return(true);
    else if(!ft_strncmp(command[0], "pwd",4))
        return(true);
    else if(!ft_strncmp(command[0], "export",7))
        return(true);
    else if(!ft_strncmp(command[0], "unset",6))
        return(true);
    else if(!ft_strncmp(command[0], "env",4))
        return(true);
    else if(!ft_strncmp(command[0], "exit",5))
        return(true);
    return (false);
}
int command_main(char **av,char **envp, t_envlist **envlst)
{
    //int pid ;
    char *command;
    const char *add_path = "/bin/";
    //pid = fork();
    //if(pid < 0)
    //{
        //error errono使う
    //}
    //tmp = av[1]; //strdup?
    // if (!tmp)
    //どこかで_=を追加する
    if(builtin_select(av))
        return (return_builtin(av, envlst));
    command = NULL;
    if(ft_strncmp(av[0], add_path, 4) != 0)
        command = ft_strjoin(add_path, av[0]);
    else
        command = ft_strdup(av[0]);
    if(command == NULL)
        return (MALLOC_ERROR);
    //ここでファイルあるか確認してaccses使う
    //commandなんちゃら追加
    execve(command, av, envp);
    if(errno)
    {
        //commandなんちゃら追加
        ft_putstr_fd("bash: ",2);
        ft_putstr_fd(command, 2);
        ft_putstr_fd(": ", 2);
        ft_putendl_fd(strerror(errno),2);
        exit(errno);
    }
    return 1;
}