/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_redirect2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyohei <wyohei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 23:45:23 by wyohei            #+#    #+#             */
/*   Updated: 2022/02/23 20:55:41 by wyohei           ###   ########.fr       */
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
		free(redirect->tmpfile);
	}
	redirect->fd = -1;
}
