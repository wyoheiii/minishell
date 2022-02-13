/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_c.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyohei <wyohei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 18:39:52 by wyohei            #+#    #+#             */
/*   Updated: 2022/02/12 21:35:59 by wyohei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
#define EXIT 1
#define EQUAL 0
#define NOT_EQUAL 1

typedef struct s_envlist
{

    char *key;
    char *value;
    struct s_envlist *next;
} t_envlist;

typedef struct s_pipe
{

    int (*pipe_fd)[2];
    pid_t *pid;
    int status;
}  t_pipe;
typedef struct s_god
{
    t_parsed *parsed;
    char *pwd;
} t_god;

int			command_part(t_parsed *parsed,t_envlist **lst);
int			my_echo(char **command);
int			my_pwd(void);
int			my_exit(char **command);
int			my_cd(char **command, t_envlist **lst);
void		print_err(char *command, char *error);
void		env_init(char **env, t_envlist **envlst);
t_envlist	*env_new(char *envp);
t_envlist	*env_lstlast(t_envlist	*lst);
void		lst_add_front(t_envlist **lst, t_envlist *new);
void		lstadd_back(t_envlist **lst, t_envlist *new);
void		all_env_clear(t_envlist **lst);
void		env_delone(t_envlist *lst);
int			my_env(t_envlist *envlst);
int			my_export(char **command,t_envlist **lst);
int			isenv(int	c);
char		*env_get_value(char *env);
char		*env_get_key(char *env);
int			my_unset(char **args,t_envlist **envlst);
bool		char_check(char *arg);
void		*god_malloc(size_t size);
size_t		env_lst_size(t_envlist *lst);
char		*search_env_key_(const char *search, t_envlist *lst);
void		dup_value(char *arg, t_envlist **lst);
void		split_free(char **split);
void		my_pipe(int *pipefd);
void		waitpid_get_status(pid_t pid, int *status,int option);
void		exit_error(char *error);
void		my_dup2(int old_fd, int newfd);
int			my_dup(int old_fd);
void		my_close(int fd);
void		*my_malloc(size_t size);
char		*strjoinjoin(char *str1, char *str2, char *str3);
pid_t		my_fork(void);
char		**lst_in_array(t_envlist *lst);
char		*strjoinjoin(char *str1, char *str2, char *str3);
void		free_array(char **array);
char		*check_access(char **path,char  *command);
char		*check_access_f(char **path,char *command);
char		*get_path(t_envlist *lst, char *command);
void		exec_error(char *command,t_envlist *lst);
bool		redirect_check(t_parsed *parsed);
int			return_builtin(char **command, t_envlist **envlst, t_god god);
int			single_builtin(t_god god,t_envlist **lst);
bool		builtin_select(char **command);
int			single_command(t_god god,t_envlist **lst);
void		multi_command(t_pipe pipe,t_envlist **lst, t_god god,int pipe_count);
void		pipe_init(t_pipe *p, int pipe_count);
void		multi_pipe(int (*pipe_fd)[2], int i,int pipe_count);
void		select_command(t_god god, t_envlist **lst);
int			isenv(int	c);
int			is_alpha_(int c);
void		dup_value(char *arg, t_envlist **lst);
void		join_value(char *arg, t_envlist **lst);
bool		set_key_value(char *arg, t_envlist **lst);
int			print_export_env(t_envlist *lst);
bool		char_check(char *arg);
bool		check_arg2(char *arg, size_t i);
bool		check_arg(char *arg,int *join_flag);
bool		key_match_check(char *arg, t_envlist *lst);
int			command_size(char **arg);
void        check_period(t_parsed *parsed);
#endif