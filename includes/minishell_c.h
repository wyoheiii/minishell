/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_c.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyohei <wyohei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 18:39:52 by wyohei            #+#    #+#             */
/*   Updated: 2022/02/23 20:04:19 by wyohei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_C_H
# define MINISHELL_C_H
# include "minishell.h"
# include "sig.h"
# include "delimiter.h"
# include "flag.h"
# include "lexer.h"
# include "parser.h"
# include "token.h"
# include "utils.h"
# include <readline/readline.h>
# include <readline/history.h>
# include "libft_utils.h"
# include "expansion.h"
# include "libft_utils.h"
# include "word_splitting.h"
# include "expand_argv.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include "libft.h"
# include <errno.h>
# include <string.h>
# include <stdbool.h>
# include "expand_argv.h"
# include <dirent.h>
# define EXIT 1
# define NO_SUCH 1
# define NOT_DIR 2
# define IS_DIR 3
# define PERM 4

typedef struct s_pipe
{
	int		(*pipe_fd)[2];
	pid_t	*pid;
	int		status;
}t_pipe;

typedef struct s_pwd
{
	char			*dir_name;
	struct s_pwd	*next;
	struct s_pwd	*prev;
}t_pwd;

typedef struct s_god
{
	t_parsed	*parsed;
	char		*pwd;
	char		*oldpwd;
}t_god;

int			command_part(t_parsed *parsed, t_envlist **lst, t_god *god);
int			my_echo(char **command);
int			my_pwd(t_god *god);
int			my_exit(char **command);
int			my_cd(char **command, t_envlist **lst, t_god *god);
void		print_err(char *command, char *error);
void		env_init(char **env, t_envlist **envlst);
t_envlist	*env_new(char *envp);
t_envlist	*env_lstlast(t_envlist	*lst);
void		lst_add_front(t_envlist **lst, t_envlist *new);
void		lstadd_back(t_envlist **lst, t_envlist *new);
void		all_env_clear(t_envlist **lst);
void		env_delone(t_envlist *lst);
int			my_env(t_envlist *envlst);
int			my_export(char **command, t_envlist **lst);
int			isenv(int	c);
char		*env_get_value(char *env);
char		*env_get_key(char *env);
int			my_unset(char **args, t_envlist **envlst);
bool		char_check(char *arg);
void		*god_malloc(size_t size);
size_t		env_lst_size(t_envlist *lst);
char		*search_env_key_(const char *search, t_envlist *lst);
void		dup_value(char *arg, t_envlist **lst);
void		split_free(char **split);
void		my_pipe(int *pipefd);
void		waitpid_get_status(pid_t pid, int *status, int option);
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
char		*check_access(char **path, char *command);
char		*check_access_f(char **path, char *command);
char		*get_path(t_envlist *lst, char *command);
void		exec_error(char *path, char *command, struct stat st);
bool		redirect_check(t_parsed *parsed);
int			return_builtin(char **command, t_envlist **envlst, t_god *god);
int			single_builtin(t_god *god, t_envlist **lst);
bool		builtin_select(char **command);
int			single_command(t_god *god, t_envlist **lst);
void		multi_command(t_pipe pipe, t_envlist **lst, \
t_god *god, int pipe_count);
void		pipe_init(t_pipe *p, int pipe_count);
void		multi_pipe(int (*pipe_fd)[2], int i, int pipe_count);
void		select_command(t_god *god, t_envlist **lst);
int			isenv(int	c);
int			is_alpha_(int c);
void		dup_value(char *arg, t_envlist **lst);
void		join_value(char *arg, t_envlist **lst);
bool		set_key_value(char *arg, t_envlist **lst);
int			print_export_env(t_envlist *lst);
bool		char_check(char *arg);
bool		check_arg2(char *arg, size_t i);
bool		check_arg(char *arg, int *join_flag);
bool		key_match_check(char *arg, t_envlist *lst);
int			command_size(char **arg);
void		check_period(t_parsed *parsed);
int			select_redirect(t_redirect *redirect);
bool		set_heredoc(t_parsed *parsed, t_envlist *lst);
int			my_heredoc(t_redirect *redirect, t_envlist *lst);
void		hedoc_fd(t_redirect *redirect);
int			syntax_check(t_parsed *parsed);
void		set_exec(t_god *god, t_envlist **lst);
void		pwd_add_back(t_pwd **top, t_pwd *new);
t_pwd		*pwd_new(char *dir);
void		pwd_lstclear(t_pwd	**lst);
void		cmd_not_fo(char *str);
char		**path_split(char const	*s, char	c);
bool		exit_atoi(char *str, long long *num);
void		set_pwd(char *pwd, char *value, t_envlist **lst);
int			cd_err(int errr, char *err);
char		*get_cd_path(char *command, t_envlist **lst);
int			nosuch_err(char *err);
int			cd_error(char *error);
void		del_period(t_pwd **pwd);
void		del_current(t_pwd **pwd, t_pwd **top, bool flag);
void		pwd_splitarray_to_list(char *path, t_pwd **pwd);
int			ret_err_period(char *path, t_god *god, t_envlist **lst, bool flag);
void		new_pwd_oldpwd(t_god *god, t_envlist **lst, char *path);
void		set_new_pwd(t_god *god, char *path, \
t_envlist **lst, char *err_path);
bool		end_slash(char *path);
char		*join_path(t_pwd *pwd);
char		*create_path(char *path, t_god *god);
bool		current_dir_check(void);
void		print_error(char *command, int ret);
char		*check_current(char *command, char *path);
void		lst_unset(char *arg, t_envlist **lst);
bool		check_digit(char *str);
bool		check_koron(char *path);
void		is_a_dir(char *str);
#endif