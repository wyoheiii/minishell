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
bool redirect_check(t_parsed *parsed)
{
    if(parsed->state == REDIRECT_APPEND)
        return(true);
    if(parsed->state == REDIRECT_OUTPUT)
        return(true);
    if(parsed->state == REDIRECT_INPUT)
        return(true);
    return(false);
}
int single_command(t_parsed *parsed, t_envlist **lst)
{
    pid_t pid;
    char *path;
    int status;
    char **env_array;

    env_array = lst_in_array( *lst);
//    if(redirect_check(parsed))
//        select_redirect(parsed);
    if(builtin_select(parsed->command))
        return (return_builtin(parsed->command, lst));
    pid = my_fork();
    if (pid == 0)
    {
        if(redirect_check(parsed))
            select_redirect(parsed);
        path = get_path(*lst, parsed->command[0]);
        if(execve(path, parsed->command, env_array) == -1)
            exec_error(path);
        free(path);
    }
    //ctrl c tokano signal moireru
    waitpid_get_status(pid,&status,0);
    free_array(env_array);
    return (0);
}

void select_command(t_parsed *parsed, t_envlist **lst)
{
    char **lst_array;
    char *path;
    lst_array = lst_in_array(*lst);
    path = get_path(*lst,parsed->command[0]);
    if(builtin_select(parsed->command))
    {
        return_builtin(parsed->command,lst);
        exit(g_status);
    }
    if(execve(path, parsed->command, lst_array)== -1)
        exec_error(path);
}

void multi_pipe(int (*pipe_fd)[2], int i,int pipe_count)
{
    if (i == 0)
    {
        my_dup2(pipe_fd[i][1], 1);
        my_close(pipe_fd[i][0]);
        my_close(pipe_fd[i][1]);
    }
    else if (i == pipe_count)
    {
        my_dup2(pipe_fd[i - 1][0], 0);
        my_close(pipe_fd[i - 1][0]);
        my_close(pipe_fd[i - 1][1]);
    }
    else
    {
        my_dup2(pipe_fd[i - 1][0], 0);
        my_dup2(pipe_fd[i][1], 1);
        my_close(pipe_fd[i - 1][0]);
        my_close(pipe_fd[i - 1][1]);
        my_close(pipe_fd[i][0]);
        my_close(pipe_fd[i][1]);
    }
}
void pipe_init(t_pipe *p, int pipe_count)
{
    p->i = 0;
    p->pipe_fd = my_malloc(sizeof(int *) * (pipe_count + 1));
    p->pid = my_malloc(sizeof(int) * (pipe_count + 1));
}
void mult_command(t_pipe p,t_parsed *parsed,t_envlist  **lst,int pipe_count)
{
    DEBUG_PRINT("a\n")
    while(parsed != NULL)
    {
        if(p.i != pipe_count && parsed->state == PIPE)
            my_pipe(p.pipe_fd[p.i]);
        p.pid[p.i] = my_fork();
        if(p.pid[p.i] == 0)
        {
            if(redirect_check(parsed))
                select_redirect(parsed);

            multi_pipe(p.pipe_fd,p.i,pipe_count);
            select_command(parsed,lst);
        }
        else if (p.i > 0)
        {
            my_close(p.pipe_fd[p.i - 1][0]);
            my_close(p.pipe_fd[p.i - 1][1]);
        }
        p.i++;
        parsed = parsed->next;
    }
}
int command_part(t_parsed *parsed, t_envlist **lst)
{
    t_pipe p;
    int pipe_count;

    pipe_count = count_pipe(parsed);
    if(pipe_count == 0)
        return (single_command(parsed, lst));
    pipe_init(&p, pipe_count);
    mult_command(p,parsed,lst,pipe_count);
    p.i = -1;
    while(++p.i < pipe_count + 1)
        waitpid_get_status(p.pid[p.i],&p.status, 0);
    free(p.pipe_fd);
    free(p.pid);
    return(0);
}