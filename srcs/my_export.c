/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyohei <wyohei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 18:17:20 by wyohei            #+#    #+#             */
/*   Updated: 2022/02/12 20:07:34 by wyohei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_c.h"

void	export_error(char *error)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	g_status = 1;
}

int	my_export(char **arg, t_envlist **lst)
{
	int		error_flag;
	size_t	i;
	int		ret_flag;

	ret_flag = 0;
	if (arg[1] == NULL)
		return (print_export_env(*lst));
	error_flag = 0;
	i = 1;
	while (arg[i] != NULL)
	{
		if (!set_key_value(arg[i], lst))
		{
			ret_flag = 1;
			error_flag = 1;
		}
		if (error_flag)
			export_error(arg[i]);
		error_flag = 0;
		i++;
	}
	if (!ret_flag)
		g_status = 0;
	return (0);
}
