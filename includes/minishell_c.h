#ifndef MINISHELL_C_H
#define MINISHELL_C_H
#include "minishell.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include "libft.h"
#include <errno.h>
#include <string.h>
#include <stdbool.h>
//#define DEBUG 1

#if DEBUG == 1
#define DEBUG_PRINT(fmt, ...) \
 		do { \
 			printf("[debug] %s:%d:\t" fmt, __FILE__, __LINE__, ##__VA_ARGS__); \
 		} while (0);
#else
#define DEBUG_PRINT(fmt, ...) do {} while(0);
#endif
#define EXIT 1
#define EQUAL 0
#define NOT_EQUAL 1
typedef struct s_envlist
{
    //int flag;
    char *key;
    char *value;
    struct s_envlist *next;
}   t_envlist;

typedef struct s_pipe
{
    //int i;
    int (*pipe_fd)[2];
    pid_t *pid;
    int status;
}   t_pipe;
typedef struct s_god
{
    t_envlist **envlist;
    t_parsed *parsed;
    char *pwd;
}   t_god;

int command_part(t_parsed *parsed,t_envlist **lst);
int my_echo(char **command);
int my_pwd(char *pwd);
int my_exit(char **command);
int my_cd(char **command, t_envlist **lst);
void print_err(char *command, char *error);
void    env_init(char **env, t_envlist **envlst);
t_envlist   *env_new(char *envp);
t_envlist	*env_lstlast(t_envlist	*lst);
void lst_add_front(t_envlist **lst, t_envlist *new);
void	lstadd_back(t_envlist **lst, t_envlist *new);
void all_env_clear(t_envlist **lst);
void	env_delone(t_envlist *lst);
int my_env(t_envlist *envlst);
int my_export(char **command,t_envlist **lst);
int	isenv(int	c);
char *env_get_value(char *env);
char *env_get_key(char *env);
int my_unset(char **args,t_envlist **envlst);
bool char_check(char *arg);
void	*god_malloc(size_t size);
size_t env_lst_size(t_envlist *lst);
char *search_env_key_(const char *search, t_envlist *lst);
void split_free(char **split);
//int multi_command(t_parsed *parsed, t_envlist **lst, char **env_array);
//int my_env()
void dup_value(char *arg, t_envlist **lst);
bool key_match_check(char *arg, t_envlist *lst);
void my_pipe(int *pipefd);
void waitpid_get_status(pid_t pid, int *status,int option);
void exit_error(char *error);
void my_dup2(int old_fd, int newfd);
int my_dup(int old_fd);
void my_close(int fd);
void	*my_malloc(size_t size);
char *strjoinjoin(char *str1, char *str2, char *str3);
pid_t my_fork(void);
#endif 