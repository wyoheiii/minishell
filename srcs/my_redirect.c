/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyohei <wyohei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 18:17:35 by wyohei            #+#    #+#             */
/*   Updated: 2022/02/12 20:38:27 by wyohei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_redirect.h"
//: syntax error near unexpected token `newline'
void	redirect_error(void)
{
	ft_putendl_fd("minishell : syntax error near unexpected \
	token `newline'", 2);
}

int	redirect_append(t_redirect *redirect)
{
	int	fd;

	if (redirect->filename != NULL)
	{
		fd = open(redirect->filename, O_WRONLY | O_APPEND | O_CREAT, 0666);
		if (fd == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(redirect->filename, 2);
			ft_putstr_fd(" :", 2);
			ft_putendl_fd(strerror(errno), 2);
			g_status = 1;
			return (fd);
		}
		my_dup2(fd, 1);
		my_close(fd);
		return (fd);
	}
	else
		redirect_error();
	return (-1);
}

int	redirect_output(t_redirect *redirect)
{
	int	fd;

	if (redirect->filename != NULL)
	{
		fd = open(redirect->filename, O_WRONLY | O_TRUNC | O_CREAT, 0666);
		if (fd == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(redirect->filename, 2);
			ft_putstr_fd(" :", 2);
			ft_putendl_fd(strerror(errno), 2);
			g_status = 1;
			return (fd);
		}
		my_dup2(fd, 1);
		my_close(fd);
		return (fd);
	}
	else
		redirect_error();
	return (-1);
}

int	redirect_input(t_redirect *redirect)
{
	int	fd;

	if (redirect->filename != NULL)
	{
		fd = open(redirect->filename, O_RDONLY);
		if (fd == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(redirect->filename, 2);
			ft_putstr_fd(" :", 2);
			ft_putendl_fd(strerror(errno), 2);
			g_status = 1;
			return (fd);
		}
		my_dup2(fd, 0);
		my_close(fd);
		return (fd);
	}
	else
		redirect_error();
	return (-1);
}

int	select_redirect(t_redirect *redirect)
{
	int	fd;

	while (redirect != NULL)
	{
		if (redirect->state == REDIRECT_INPUT)
			fd = redirect_input(redirect);
		if (redirect->state == REDIRECT_OUTPUT)
			fd = redirect_output(redirect);
		if (redirect->state == REDIRECT_APPEND)
			fd = redirect_append(redirect);
		if (redirect->state == HERE_DOCUMENT)
		{
			if (redirect->fd > 0)
			{
				my_dup2(redirect->fd, 0);
				my_close(redirect->fd);
			}
			redirect->fd = -1;
		}
		if ((redirect->state == REDIRECT_APPEND || \
		redirect->state == REDIRECT_OUTPUT || \
		redirect->state == REDIRECT_INPUT) && fd == -1)
			break ;
		redirect = redirect->next;
	}
    return (fd);
}
