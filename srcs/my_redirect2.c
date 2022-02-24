/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_redirect2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkaneshi <tkaneshi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 23:45:23 by wyohei            #+#    #+#             */
/*   Updated: 2022/02/24 22:04:35 by tkaneshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
void	hedoc_fd(t_redirect *redirect)
{
	if (redirect->fd > 0)
	{
		redirect->fd = open(redirect->tmpfile, O_RDONLY);
		my_dup2(redirect->fd, 0);
		my_close(redirect->fd);
	}
	if (redirect->tmpfile)
	{
		unlink(redirect->tmpfile);
	}
	redirect->fd = -1;
}
