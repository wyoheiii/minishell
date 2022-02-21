/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_cd2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyohei <wyohei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 15:12:10 by wyohei            #+#    #+#             */
/*   Updated: 2022/02/21 16:31:09 by wyohei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_c.h"
void	new_pwd_oldpwd(t_god *god, t_envlist **lst, char *path)
{
	char	*new;

	if (god->oldpwd != NULL)
		free(god->oldpwd);
	god->oldpwd = my_strdup(god->pwd);
	if (!end_slash(god->pwd))
		new = strjoinjoin(god->pwd, "/", path);
	else
		new = ft_strjoin(god->pwd, path);
	if (new == NULL)
		exit_error("malloc");
	set_pwd("PWD", new, lst);
	set_pwd("OLDPWD", god->pwd, lst);
	if (god->pwd != NULL)
		free(god->pwd);
	god->pwd = my_strdup(new);
	free(new);
}

int	ret_err_period(char *path, t_god *god, t_envlist **lst, bool flag)
{
	ft_putstr_fd("cd :error retrieving current directory: ", 2);
	ft_putstr_fd("getcwd: cannot access parent directories: ", 2);
	ft_putendl_fd("No such file or directory", 2);
	new_pwd_oldpwd(god, lst, path);
	if (flag)
		free(path);
	g_status = 0;
	return (0);
}

void	pwd_splitarray_to_list(char *path, t_pwd **pwd)
{
	char	**split;
	int		i;

	i = 0;
	split = my_split(path, '/');
	while (split[i] != NULL)
	{
		pwd_add_back(pwd, pwd_new(my_strdup(split[i])));
		i++;
	}
	split_free(split);
}

void	del_current(t_pwd **pwd, t_pwd **top, bool flag)
{
	t_pwd	*tmp;

	tmp = *pwd;
	if (*pwd == NULL)
		return ;
	tmp = *pwd;
	if ((*pwd)->prev == NULL)
	{
		(*pwd) = (*pwd)->next;
		if (*pwd)
			(*pwd)->prev = NULL;
		*top = *pwd;
		if (*pwd != NULL && flag)
			*pwd = (*pwd)->next;
		free(tmp->dir_name);
		free(tmp);
		return ;
	}
	(*pwd)->prev->next = (*pwd)->next;
	if ((*pwd)->next != NULL)
		(*pwd)->next->prev = (*pwd)->prev;
	if (*pwd != NULL && flag)
		*pwd = (*pwd)->next;
	free(tmp->dir_name);
	free(tmp);
}

void	del_period(t_pwd **pwd)
{
	t_pwd	*top;

	top = *pwd;
	while (*pwd != NULL)
	{
		if (*pwd != NULL && ft_strncmp((*pwd)->dir_name, "..", 3) == 0)
		{
			if ((*pwd)->prev != NULL)
				del_current(&(*pwd)->prev, &top, false);
			del_current(pwd, &top, true);
			continue ;
		}
		if (*pwd != NULL && (ft_strncmp((*pwd)->dir_name, ".", 2) == 0))
		{
			del_current(pwd, &top, true);
			continue ;
		}
		if (*pwd)
			*pwd = (*pwd)->next;
	}
	*pwd = top;
}
