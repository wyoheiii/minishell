/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_util4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyohei <wyohei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 16:44:28 by wyohei            #+#    #+#             */
/*   Updated: 2022/02/21 22:17:59 by wyohei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_c.h"

void	print_error(char *command, int ret)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(command, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(strerror(errno), 2);
	exit(ret);
}

int	check_perm_status(char *command, char *path, struct stat st)
{
	if ((st.st_mode & S_IFREG) && ft_strncmp(path, "./", 2) == 0 \
	&& ft_strncmp(command, "./", 2))
		cmd_not_fo(command);
	if (!(st.st_mode & S_IRUSR))
		return (EACCES);
	if (!(st.st_mode & S_IXUSR))
		return (EACCES);
	if (access(command, X_OK) != 0)
		return (EACCES);
	exit(0);
}

void	exec_error(char *path, char *command, struct stat st)
{
	int	ret;

	ret = 127;
	if (errno != ENOENT)
		ret = 126;
	if (errno == ENOEXEC)
		errno = check_perm_status(command, path, st);
	print_error(command, ret);
}

void	cmd_not_fo(char *str)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd("command not found", 2);
	exit(127);
}
