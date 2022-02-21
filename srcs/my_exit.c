/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyohei <wyohei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 18:17:07 by wyohei            #+#    #+#             */
/*   Updated: 2022/02/21 15:10:57 by wyohei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_c.h"

bool	check_num(char *command)
{
	size_t	i;

	i = 0;
	if (command[0] == '+' || command[0] == '-')
	{
		i++;
		if (command[i] == '\0')
			return (false);
	}
	while (command[i] != '\0')
	{
		if (!ft_isdigit(command[i]))
			return (false);
		i++;
	}
	return (true);
}


int	exit_error_c(char *error)
{
	if (error == NULL)
	{
		g_status = 1;
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (0);
	}
	else
	{
		g_status = 255;
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(error, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		return (EXIT);
	}
}
int	my_exit2(char **command, int size, long long num)
{
	if (check_num(command[1]) && !exit_atoi(command[1], &num))
		return (exit_error_c(command[1]));

	if (size == 2 && check_num(command[1]))
		return (EXIT);
	if (size > 2 && check_num(command[1]))
		return (exit_error_c(NULL));
	else if (size > 1)
		return (exit_error_c(command[1]));
	g_status = 0;
	return(EXIT);
}

int	my_exit(char **command)
{
	int			size;
	long long	num;
	char		*str;

	ft_putendl_fd("exit", 2);
	size = command_size(command);
	num = 0;
	if (size == 1)
		return (EXIT);
	str = ft_strtrim(command[1], " ");
	if (str == NULL)
		exit_error("malloc");
	if (str[0] != '\0' && size == 2 && check_num(str) && exit_atoi(str, &num))
	{
		free(str);
		g_status = (unsigned char)num;
		return (EXIT);
	}
	free(str);
	return (my_exit2(command, size, num));
}
