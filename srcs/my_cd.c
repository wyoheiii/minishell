/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyohei <wyohei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 18:16:55 by wyohei            #+#    #+#             */
/*   Updated: 2022/02/15 00:21:53 by wyohei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_c.h"

int	cd_error(char *error)
{
	if (error == NULL)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		g_status = 1;
		return (0);
	}
	else
	{
		g_status = 1;
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(error, 2);
		return (0);
	}
}

void	set_pwd(t_envlist **lst, char *pwd)
{
	char	*key_value;
	char	*cwd;

	if (key_match_check(pwd, *lst))
	{
		cwd = getcwd(NULL, 0);
		if (cwd == NULL)
			return ;
		key_value = strjoinjoin(pwd, "=", cwd);
		dup_value(key_value, lst);
		free(key_value);
		free(cwd);
	}
}
int chdir_err(char *err)
{
    g_status = 1;
    ft_putstr_fd("minishell : cd :", 2);
    ft_putstr_fd(err, 2);
    ft_putstr_fd(":", 2);
    ft_putendl_fd(strerror(errno), 2);
    return (0);
}
int cd_home(t_envlist **lst, t_god god)
{
    char *path;
    (void)god;
    path = search_env_key_("HOME", *lst);
    if (path == NULL)
        return (cd_error(NULL));
    if (chdir(path) != 0)
        chdir_err(path);
    return (0);
}
int	my_cd(char **command, t_envlist **lst, t_god god)
{
	//char	*path;
	char	*error;

	set_pwd(lst, "OLDPWD");
	if (command[1] == NULL)
        return(cd_home(lst, god));
	else if (chdir(command[1]) != 0)
	{
		error = ft_strjoin("minishell: cd: ", command[1]);
		if (error == NULL)
			exit_error("malloc");
		g_status = 1;
		perror(error);
		free(error);
		return (0);
	}
	set_pwd(lst, "PWD");
	g_status = 0;
	return (0);
}
