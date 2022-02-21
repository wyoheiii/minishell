/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_cd3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyohei <wyohei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 15:12:13 by wyohei            #+#    #+#             */
/*   Updated: 2022/02/21 16:32:55 by wyohei           ###   ########.fr       */
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
		ft_putstr_fd(" :", 2);
		ft_putendl_fd(strerror(errno), 2);
		return (0);
	}
}

int	nosuch_err(char *err)
{
	g_status = 1;
	ft_putstr_fd("minishell : cd : ", 2);
	ft_putstr_fd(err, 2);
	ft_putstr_fd(":", 2);
	ft_putendl_fd(": No such file or directory", 2);
	return (0);
}

char	*get_cd_path(char *command, t_envlist **lst)
{
	char	*path;

	if (command == NULL)
	{
		path = search_env_key_("HOME", *lst);
		if (path == NULL)
			return (NULL);
		return (my_strdup(path));
	}
	return (my_strdup(command));
}

int	cd_err(int errr, char *err)
{
	errno = errr;
	g_status = 1;
	ft_putstr_fd("minishell : cd :", 2);
	ft_putstr_fd(err, 2);
	ft_putstr_fd(":", 2);
	ft_putendl_fd(strerror(errno), 2);
	return (0);
}

void	set_pwd(char *pwd, char *value, t_envlist **lst)
{
	char	*keyvalue;

	if (key_match_check(pwd, *lst))
	{
		keyvalue = strjoinjoin(pwd, "=", value);
		dup_value(keyvalue, lst);
		free(keyvalue);
	}
}
