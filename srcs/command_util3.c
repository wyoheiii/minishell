/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_util3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyohei <wyohei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 23:10:11 by wyohei            #+#    #+#             */
/*   Updated: 2022/02/15 15:27:42 by wyohei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_c.h"

void	check_period(t_parsed *parsed)
{
	if (parsed != NULL)
	{
		if (parsed->command[0] != NULL)
		{
			if (ft_strncmp(parsed->command[0], "..", 3) == 0 || \
			ft_strncmp(parsed->command[0], ".", 2) == 0)
			{
				ft_putstr_fd("minishell: ", 2);
				ft_putstr_fd(parsed->command[0], 2);
				ft_putstr_fd(": ", 2);
				ft_putendl_fd("command not found", 2);
				exit(127);
			}
		}
	}
}

void	set_exec(t_god god, t_envlist **lst)
{
	char	*path;
	char	**env_array;

	env_array = lst_in_array(*lst);
	path = get_path(*lst, god.parsed->command[0]);
	if (execve(path, god.parsed->command, env_array) == -1)
	{
        free_array(env_array);
		exec_error(path, *lst);
	}
}
