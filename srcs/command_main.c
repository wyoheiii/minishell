#include "../inc/minishell_c.h"

bool    builtin_select(char **command)
{
    if(!ft_strncmp(command[0], "echo",5))//command[0];
        return(my_echo(command));
    if(!ft_strncmp(command[0], "cd",3))
        return(true);
    if(!ft_strncmp(command[0], "pwd",4))
        return(my_pwd());
    if(!ft_strncmp(command[0], "export",7))
        return(true);
    if(!ft_strncmp(command[0], "unset",6))
        return(true);
    if(!ft_strncmp(command[0], "env",4))
        return(true);
    if(!ft_strncmp(command[0], "exit",5))
        return(my_exit(command)); //構造体でretの値渡したほうがいいかもしれん
    return (false);
}
void command_main(char **av,char **envp)//intでいいかも
{
    //int pid ;
    //printf("args:%s\n",av[0]);
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
    if(builtin_select(av))// return de ビルドインの戻り値を返す
        return ; //return de ビルドインの戻り値を返す
    if(ft_strncmp(av[0], add_path, 4) != 0)//av[0]
        command = ft_strjoin(add_path, av[0]);//av[0]
    //if(command == NULL)
    //     return NULL;
    else
         command = av[0]; //av[0]
    printf("linne::::%s\n",command);
    //printf("envp::%s\n",envp[1]);
    av++; //ここも修正
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
}