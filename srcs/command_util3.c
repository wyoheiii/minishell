/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_util3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyohei <wyohei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 23:10:11 by wyohei            #+#    #+#             */
/*   Updated: 2022/02/22 15:46:02 by wyohei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_c.h"

void	check_period(t_parsed *parsed)
{
	if (ft_strncmp(parsed->command[0], "..", 3) == 0 || \
	ft_strncmp(parsed->command[0], ".", 2) == 0 || \
	ft_strncmp(parsed->command[0], "\0", 1) == 0)
		cmd_not_fo(parsed->command[0]);
}

void	set_exec(t_god *god, t_envlist **lst)
{
	char		*path;
	char		**env_array;
	struct stat	st;

	if (god->parsed->command[0] == NULL)
		exit(0);
	path = get_path(*lst, god->parsed->command[0]);
	stat(path, &st);
	env_array = lst_in_array(*lst);
	if (execve(path, god->parsed->command, env_array) == -1)
	{
		free_array(env_array);
		exec_error(path, god->parsed->command[0], st);
	}
}
