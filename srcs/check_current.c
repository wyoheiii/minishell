/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_current.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyohei <wyohei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 22:14:28 by wyohei            #+#    #+#             */
/*   Updated: 2022/02/21 22:15:59 by wyohei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_c.h"

bool	check_koron(char *path)
{
	size_t	size;
	int		i;

	i = 0;
	size = ft_strlen(path);
	if (path[i] == ':')
		return (true);
	if (path[size - 1] == ':')
		return (true);
	while (path[i] != '\0')
	{
		if (path[i] == ':' && path[i + 1] == ':')
			return (true);
		i++;
	}
	return (false);
}

char	*check_current(char *command, char *path)
{
	struct stat	st;
	char		*new_path;

	if (path[0] == '\0')
		return (command);
	if (!check_koron(path))
		cmd_not_fo(command);
	new_path = ft_strjoin("./", command);
	if (new_path == NULL)
		exit_error("malloc");
	if (stat(new_path, &st) != 0)
	{
		free(new_path);
		cmd_not_fo(command);
	}
	if (S_ISDIR(st.st_mode))
	{
		free(new_path);
		cmd_not_fo(command);
	}
	free(new_path);
	return (command);
}
