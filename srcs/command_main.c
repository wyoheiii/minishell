#include "minishell_c.h"

int    return_builtin(char **command, t_envlist **envlst, t_god god)
{
    int ret;

    ret = 0;
    if(command[0] == NULL)
        return (0);
    if(!ft_strncmp(command[0], "echo", 5))
        ret = my_echo(command);
    else if(!ft_strncmp(command[0], "cd", 3))
        ret = my_cd(command, envlst);
    else if(!ft_strncmp(command[0], "pwd", 4))
        ret = my_pwd(god.pwd);
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
    if(command[0] == NULL)
        return(true);
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
        if(lst->value == NULL)
            ret[i] = ft_strdup("");
        else
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

void exec_error(char *command,t_envlist *lst)
{
    //bash: ls: No such file or directory path消すとこうなるらしい
    char *path;
    path= search_env_key_("PATH",lst);
    if(strchr(command, '/') == NULL && path != NULL)
    {
        ft_putstr_fd("minishell: ", 2);
        ft_putstr_fd(command, 2);
        ft_putstr_fd(": ", 2);
        ft_putendl_fd("command not found", 2);
        exit(127);
    }
    else if (errno)
    {
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
    if(parsed->redirect != NULL)
    {
        if (parsed->redirect->state == REDIRECT_APPEND)
            return (true);
        if (parsed->redirect->state == REDIRECT_OUTPUT)
            return (true);
        if (parsed->redirect->state == REDIRECT_INPUT)
            return (true);
        if (parsed->redirect->state == HERE_DOCUMENT)
            return (true);
    }
    return(false);
}

int single_builtin(t_god god,t_envlist **lst)
{
    int fd1;
    int fd2;
    int fd3;
    int ret;

    fd1 = my_dup(0);
    fd2 = my_dup(1);
    fd3 = my_dup(2);
    if(redirect_check(god.parsed))
        select_redirect(god.parsed->redirect);
    ret = return_builtin(god.parsed->command, lst,god);
    my_dup2(fd1,0);
    my_dup2(fd2,1);
    my_dup2(fd3,2);
    my_close(fd1);
    my_close(fd2);
    my_close(fd3);
    return(ret);
}
int single_command(t_god god,t_envlist **lst)
{
    pid_t pid;
    char *path;
    int status;
    char **env_array;

    env_array = lst_in_array( *lst);

    if(builtin_select(god.parsed->command))
        return (single_builtin(god,lst));
    //printf("fd  ; %d\n",parsed->redirect->fd);
    pid = my_fork();
    if (pid == 0)
    {
        if(redirect_check(god.parsed))
            select_redirect(god.parsed->redirect);
        path = get_path(*lst,god.parsed->command[0]);
        if(execve(path, god.parsed->command, env_array) == -1)
            exec_error(path,*lst);
        free(path);
        //exit(g_status);
    }
    else
        waitpid_get_status(pid,&status,0);
    //signal irukamo
    free_array(env_array);
    return (0);
}

void select_command(t_god god, t_envlist **lst)
{
    char **lst_array;
    char *path;
    lst_array = lst_in_array(*lst);
    path = get_path(*lst,god.parsed->command[0]);
    if(builtin_select(god.parsed->command))
    {
        single_builtin(god, lst);
        exit(g_status);
    }
    if(redirect_check(god.parsed))
        select_redirect(god.parsed->redirect);
    if(execve(path, god.parsed->command, lst_array)== -1)
        exec_error(path,*lst);
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
    p->pipe_fd = my_malloc(sizeof(int *) * (pipe_count + 1));
    p->pid = my_malloc(sizeof(int) * (pipe_count + 1));
}
void mult_command(t_pipe pipe,t_envlist **lst, t_god god,int pipe_count)
{
    DEBUG_PRINT("a\n")
    int i = 0;
    while(god.parsed != NULL)
    {
        if(i != pipe_count && god.parsed->state == PIPE)
            my_pipe(pipe.pipe_fd[i]);
        pipe.pid[i] = my_fork();
        if(pipe.pid[i] == 0)
        {
            multi_pipe(pipe.pipe_fd, i, pipe_count);
            select_command(god, lst);
        }
        else
        {
            if(i > 0) {
                my_close(pipe.pipe_fd[i - 1][0]);
                my_close(pipe.pipe_fd[i - 1][1]);
            }
        }
        i++;
        god.parsed = god.parsed->next;

    }
}
void god_init(t_god *god,t_parsed *parsed,t_envlist *lst)
{
    god->parsed = parsed;
    god->pwd = search_env_key_("PWD",lst);
}
int command_part(t_parsed *parsed, t_envlist **lst)
{
    t_god  god;
    t_pipe p;
    int pipe_count;
    int i;

    god_init(&god, parsed, *lst);
    pipe_count = count_pipe(god.parsed);
    set_heredoc(god.parsed);
    //printf("command :%s\n",parsed->command[0]);
    if(pipe_count == 0)
        return (single_command(god,lst));
    pipe_init(&p, pipe_count);
    mult_command(p,lst,god,pipe_count);
    i = -1;
    while(++i < pipe_count + 1)
        waitpid_get_status(p.pid[i],&p.status, 0);
    free(p.pipe_fd);
    free(p.pid);
    return(0);
}