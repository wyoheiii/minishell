#ifndef MINISHELL_C_H
#define MINISHELL_C_H
#include <stdio.h>
#include <unistd.h>
#include "../libft/libft.h"
#include <errno.h>
#include <string.h>
#include <stdbool.h>
#define MALLOC_ERROR -2

//#define exp
typedef struct s_envlist
{
    char *key;
    char *value;
    struct s_envlist *next;
}   t_envlist;
int command_main(char **av,char **envp,t_envlist **envlst);
int my_echo(char **command);
int my_pwd(void);
int my_exit(char **command);
int my_cd(char **command);
void print_err(char *command, char *error);
bool    env_init(char **env, t_envlist **envlst);
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
//int my_env()
#endif 