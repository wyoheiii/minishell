/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_util2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkaneshi <tkaneshi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 16:19:29 by wyohei            #+#    #+#             */
/*   Updated: 2022/02/22 21:39:35 by tkaneshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_c.h"
char	**lst_in_array(t_envlist *lst)
{
	char	*tmp;
	char	**ret;
	size_t	i;

	i = 0;
	ret = (char **)malloc(sizeof(char *) * (env_lst_size(lst) + 1));
	if (!ret)
		exit_error("malloc");
	while (lst != NULL)
	{
		tmp = ft_strjoin(lst->key, "=");
		if (!tmp)
			exit_error("malloc");
		if (lst->value == NULL)
			ret[i] = my_strdup("");
		else
			ret[i] = ft_strjoin(tmp, lst->value);
		if (!ret[i])
			exit_error("malloc");
		lst = lst->next;
		i++;
		free(tmp);
	}
	ret[i] = NULL;
	return (ret);
}

char	*strjoinjoin(char *str1, char *str2, char *str3)
{
	char	*tmp;
	char	*ret;

	tmp = ft_strjoin(str1, str2);
	if (tmp == NULL)
		exit_error("malloc");
	ret = ft_strjoin(tmp, str3);
	if (ret == NULL)
		exit_error("malloc");
	free(tmp);
	return (ret);
}

char	*check_access_f(char **path, char *command)
{
	char	*access_path;
	size_t	i;

	i = 0;
	while (path[i] != NULL)
	{
		access_path = strjoinjoin(path[i], "/", command);
		if (access(access_path, F_OK) == 0)
		{
			split_free(path);
			return (access_path);
		}
		i++;
		free(access_path);
	}
	split_free(path);
	return (NULL);
}

char	*check_access(char **path, char *command)
{
	char	*access_path;
	size_t	i;

	i = 0;
	while (path[i] != NULL)
	{
		access_path = strjoinjoin(path[i], "/", command);
		if (access(access_path, X_OK) == 0)
		{
			split_free(path);
			return (access_path);
		}
		i++;
		free(access_path);
	}
	return (check_access_f(path, command));
}

char	*get_path(t_envlist *lst, char *command)
{
	char	*path;
	char	**array_path;
	char	*ret;

	if (command == NULL)
		exit(0);
	if (ft_strchr(command, '/') == NULL)
	{
		path = search_env_key_("PATH", lst);
		if (path != NULL)
		{
			if (check_koron(path))
				array_path = path_split(path, ':');
			else
				array_path = my_split(path, ':');
			ret = check_access(array_path, command);
			if (ret == NULL)
				ret = check_current(command, path);
			return (ret);
		}
	}
	is_a_dir(command);
	return (command);
}
