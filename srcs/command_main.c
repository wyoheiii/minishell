#include "minishell_c.h"

int    return_builtin(char **command, t_envlist **envlst)
{
    int ret;
    ret = 0;
    if(!ft_strncmp(command[0], "echo", 5))
        ret = my_echo(command);
    else if(!ft_strncmp(command[0], "cd", 3))
        ret = my_cd(command, *envlst);
    else if(!ft_strncmp(command[0], "pwd", 4))
        ret = my_pwd();
    else if(!ft_strncmp(command[0], "export", 7))
        ret = my_export(command, envlst);
    else if(!ft_strncmp(command[0], "unset",6))
        ret = my_unset(command, envlst);
    else if(!ft_strncmp(command[0], "env",4))
        ret = my_env(*envlst);
    else if(!ft_strncmp(command[0], "exit",5))
        ret = my_exit(command);
    return (ret);
}

bool    builtin_select(char **command)
{
    if(!ft_strncmp(command[0], "echo",5))
        return(true);
    else if(!ft_strncmp(command[0], "cd", 3))
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

char **lst_in_array(t_envlist *lst)
{
    char *tmp;
    char **ret;

    size_t i;
    i = 0;
    ret = (char **)malloc(sizeof(char *) * (env_lst_size(lst) + 1));
    if(!ret)
        exit(1);
    while(lst != NULL)
    {
        tmp = ft_strjoin(lst->key, "=");
        if(!tmp)
            exit(1);
        ret[i] = ft_strjoin(tmp,lst->value);
        if(!ret[i])
            exit(1);
        lst = lst->next;
        i++;
        free(tmp);
    }
    ret[i] = NULL;
    return (ret);
}

char *strjoinjoin(char *str1, char *str2, char *str3)
{
    char *tmp;
    char *ret;
    tmp = ft_strjoin(str1,str2);
    if(tmp == NULL)
        exit(1);
    ret = ft_strjoin(tmp, str3);
    if(ret == NULL)
        exit(1);
    free(tmp);
    return(ret);
}

char *check_access_f(char **path,char *command)
{
    char *access_path;
    size_t i;
    i = 0;
    while(path[i] != NULL)
    {
        access_path = strjoinjoin(path[i], "/", command);
        if(access(access_path,F_OK) == 0)
        {
            split_free(path);
            return (access_path);
        }
        i++;
        free(access_path);
    }
    split_free(path);
    return(NULL);
}

char *check_access(char **path,char  *command)//bash: bim/ls: No such file or directory
{
    char *access_path;
    size_t i;
    i = 0;
    while(path[i] != NULL)
    {
        access_path = strjoinjoin(path[i], "/", command);
        if(access(access_path, X_OK) == 0)
        {
            split_free(path);
            return (access_path);
        }
        i++;
        free(access_path);
    }
    access_path = check_access_f(path, command);
    if(access_path == NULL)
        return (command);
    return(command);
}

char *get_path(t_envlist *lst, char *command)
{
    char *path;
    char **array_path;
    char *cmd;
    cmd = ft_strdup(command);
    if(cmd == NULL)
        exit(1);
    if(ft_strchr(command,'/') == NULL)
    {
        path = search_env_key_("PATH", lst);
        if (path != NULL)
        {
            array_path = ft_split(path, ':');
            if (array_path == NULL)
                exit(1);
            return (check_access(array_path,cmd));
        }
    }
    return (cmd);
}

void exec_error(char *command)
{
    //bash: ls: No such file or directory path消すとこうなるらしい
    if(strchr(command, '/') == NULL)
    {
        ft_putstr_fd("minishell: ", 2);
        ft_putstr_fd(command, 2);
        ft_putstr_fd(": ", 2);
        ft_putendl_fd("command not found", 2);
        exit(127);
    }
    else if (errno)
    {
        //commandなんちゃら追加
        ft_putstr_fd("minishell: ", 2);
        ft_putstr_fd(command, 2);
        ft_putstr_fd(": ", 2);
        ft_putendl_fd(strerror(errno), 2);
        exit(127);
    }
}

int single_command(char **command, t_envlist **lst, char **env_array)
{
    pid_t pid;
    char *path;
    int status;

    if(builtin_select(command))
        return (return_builtin(command, lst));
    else {
        pid = fork();
        if (pid == -1)
            exit(1);
        else if (pid == 0)
        {
            path = get_path(*lst, command[0]);
            if(execve(path, command, env_array) == -1)
                exec_error(path);
            free(path);
        }
        //ctrl c tokano signal moireru
        if (waitpid(pid, &status, 0) < 0)
        {
            ft_putstr_fd(strerror(errno), 2);
            ft_putstr_fd("\n", 2);
            exit(errno);
        }
        if(WIFEXITED(status))
            g_status = WEXITSTATUS(status);
        return (0);
    }
}

void free_array(char **array)
{
    size_t i;
    i = 0;
    while(array[i])
    {
        free(array[i]);
        i++;
    }
    free(array);
}
int count_pipe(t_parsed *parsed)
{
    int ret;
    ret = 0;

    while(parsed != NULL)
    {
        if(parsed->state == PIPE)
            ret++;
        parsed = parsed->next;
    }
    return (ret);
}

int multi_command(t_parsed *parsed, t_envlist **lst)
{
    char *path;
    char **lst_array;
    int pipe_count;
    int (*pipe_fd)[2];
    int i;
    pid_t *pid;
    pipe_count = count_pipe(parsed);
    pipe_fd = malloc(sizeof(int *) * (pipe_count + 1));
    if(pipe_fd == NULL)
        exit(1);
    pid = malloc(sizeof(int) * (pipe_count + 1));
    if(pid == NULL)
        exit(1);
    if(pipe_count == 0)
    {
        //return(single_command);
    }
    i = 0;
    //printf("%d\n",pipe_count);
    while(parsed != NULL)
    {
        //printf("%s\n", parsed->command[0]);
        lst_array = lst_in_array(*lst);
        path = get_path(*lst,parsed->command[0]);
        if(i != pipe_count && parsed->state == PIPE){
            if(pipe(pipe_fd[i]) == -1) {
                perror("pipe");
                exit(1);
            }
        }
        pid[i] = fork();
        //printf("pid    :%d\n",pid[i]);
        if(pid[i] == 0)
        {
            if(i == 0)
            {
                dup2(pipe_fd[i][1], 1);
                close(pipe_fd[i][0]);
                close(pipe_fd[i][1]);
            }
            else if (i == pipe_count)
            {
                dup2(pipe_fd[i - 1][0], 0);
                close(pipe_fd[i - 1][0]);
                close(pipe_fd[i - 1][1]);
            }
            else
            {
                dup2(pipe_fd[i - 1][0], 0);
                dup2(pipe_fd[i][1], 1);
                close(pipe_fd[i - 1][0]);
                close(pipe_fd[i - 1][1]);
                close(pipe_fd[i][0]);
                close(pipe_fd[i][1]);
            }
            if(builtin_select(parsed->command))
            {
                //if()
                return_builtin(parsed->command,lst);
                exit(g_status);
            }
            if(execve(path, parsed->command, lst_array)== -1)
                exec_error(path);
        }
        else if (i > 0)
        {
            close(pipe_fd[i - 1][0]);
            close(pipe_fd[i - 1][1]);
        }
        free(path);
        free_array(lst_array);
        i++;
        parsed = parsed->next;
    }
    int status;


    i = 0;
    while(i < pipe_count + 1 )
    {
        if(waitpid(pid[i],&status, 0) < 0)
        {
            ft_putstr_fd(strerror(errno), 2);
            ft_putstr_fd("\n", 2);
            exit(errno);
        }
        //i--;
        i++;
    }
    if(WIFEXITED(status))
        g_status = WEXITSTATUS(status);
    free(pipe_fd);
    free(pid);
    return(0);
}

int command_part(t_parsed *parsed,t_envlist **lst)
{
    int ret;
    char **env_array;
    env_array = lst_in_array(*lst);
    if(parsed->state == NONE)
        ret = single_command(parsed->command, lst, env_array);
    else
        ret = multi_command(parsed, lst);
    free_array(env_array);
    return (ret);
}