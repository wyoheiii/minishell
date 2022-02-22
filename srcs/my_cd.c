/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyohei <wyohei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 18:16:55 by wyohei            #+#    #+#             */
/*   Updated: 2022/02/21 16:45:48 by wyohei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_c.h"

char	*join_path(t_pwd *pwd)
{
	char	*path;
	char	*tmp;

	path = NULL;
	if (pwd)
	{
		path = ft_strjoin("/", pwd->dir_name);
		if (path == NULL)
			exit_error("malloc");
		pwd = pwd->next;
	}
	while (pwd != NULL)
	{
		tmp = strjoinjoin(path, "/", pwd->dir_name);
		free(path);
		path = tmp;
		pwd = pwd->next;
	}
	return (path);
}

char	*create_path(char *path, t_god *god)
{
	char	*new_path;
	t_pwd	*pwd;

	pwd = NULL;
	new_path = strjoinjoin(god->pwd, "/", path);
	pwd_splitarray_to_list(new_path, &pwd);
	del_period(&pwd);
	free(new_path);
	new_path = join_path(pwd);
	pwd_lstclear(&pwd);
	return (new_path);
}

bool	current_dir_check(void)
{
	struct stat	sh;
	char		*cwd;

	cwd = getcwd(NULL, 0);
	if (lstat(cwd, &sh) == 0)
	{
		free(cwd);
		return (true);
	}
	return (false);
}

void	cd_free(char *str1, char *str2, char *str3)
{
	free(str1);
	free(str2);
	free(str3);
}

int	my_cd(char **command, t_envlist **lst, t_god *god)
{
	char	*path;
	char	*cwd;
	char	*new_path;

	if (command != NULL && command[1] != NULL && command[1][0] == '~')
		return (0);
	path = get_cd_path(command[1], lst);
	if (path == NULL)
		return (cd_error(NULL));
	cwd = getcwd(NULL, 0);
	if ((ft_strncmp(path, ".", 2) == 0 || \
	 ft_strncmp(path, "./", 3) == 0) && cwd == NULL)
		return (ret_err_period(path, god, lst, true));
	if (path && path[0] == '/')
		new_path = my_strdup(path);
	else
		new_path = create_path(path, god);
	if (chdir(path) != 0)
		cd_error(path);
	else
		set_new_pwd(god, new_path, lst, path);
	cd_free(new_path, cwd, path);
	return (0);
}
