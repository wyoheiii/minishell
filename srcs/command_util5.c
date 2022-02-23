/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_util5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyohei <wyohei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 20:04:44 by wyohei            #+#    #+#             */
/*   Updated: 2022/02/23 20:08:24 by wyohei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_c.h"

void	is_a_dir(char *str)
{
	struct stat	st;

	stat(str, &st);
	if (S_ISDIR(st.st_mode))
	{
		ft_putstr_fd("minishell:", 2);
		ft_putstr_fd(str, 2);
		ft_putendl_fd(": is a directory", 2);
		exit(126);
	}
}
