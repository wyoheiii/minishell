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

#include "minishell_c.h"

int	redirect_error(char *str)
{
    if(str == NULL)
    {
        ft_putendl_fd("minishell : syntax error near unexpected ", 2);
        ft_putendl_fd("token `newline'", 2);
        return(0);
    }
    else
    {
        ft_putstr_fd("bash: ", 2);
        ft_putstr_fd(str, 2);
        ft_putendl_fd(": ambiguous redirect", 2);
        return(-1);
    }
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
		redirect_error(NULL);
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
		redirect_error(NULL);
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
		redirect_error(NULL);
	return (-1);
}

int	select_redirect(t_redirect *redirect)
{
	int	fd;
    fd = 0;
	while (redirect != NULL)
	{
        if(redirect->is_error == AMBIGUOUS)
            return(redirect_error(redirect->filename));
		else if (redirect->state == REDIRECT_INPUT)
			fd = redirect_input(redirect);
		else if (redirect->state == REDIRECT_OUTPUT)
			fd = redirect_output(redirect);
		else if (redirect->state == REDIRECT_APPEND)
			fd = redirect_append(redirect);
		else if (redirect->state == HERE_DOCUMENT)
            hedoc_fd(redirect);
		if ((redirect->state == REDIRECT_APPEND || \
		redirect->state == REDIRECT_OUTPUT || \
		redirect->state == REDIRECT_INPUT) && fd == -1)
			break ;
		redirect = redirect->next;
	}
    return (fd);
}
