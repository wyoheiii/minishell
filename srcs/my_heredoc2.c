/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_heredoc2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyohei <wyohei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 23:28:00 by wyohei            #+#    #+#             */
/*   Updated: 2022/02/23 20:22:38 by wyohei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*new_file(int count)
{
	char		*ret;
	const char	*tmp = "/tmp/";
	char		*idx;

	idx = ft_itoa(count);
	if (!idx)
		exit_error("malloc");
	ret = ft_strjoin(tmp, idx);
	if (!ret)
		exit_error("malloc");
	free(idx);
	return (ret);
}

bool	heredoc_count_check(int count, int *fd)
{
	if (count == INT_MAX)
	{
		ft_putendl_fd("too many file", 2);
		*fd = -1;
		return (true);
	}
	return (false);
}

int	create_heredoc_file(int count, char **tmpfile)
{
	struct stat	st;
	int			fd;

	while (1)
	{
		if (heredoc_count_check(count, &fd))
			break ;
		*tmpfile = new_file(count);
		if (stat(*tmpfile, &st) == 0)
		{
			free(*tmpfile);
			count++;
			continue ;
		}
		fd = open(*tmpfile, O_WRONLY | O_EXCL | O_CREAT, 0666);
		if (fd == -1)
			ft_putendl_fd("open dekimasen", 2);
		break ;
	}
	if (*tmpfile && fd == -1)
		free(*tmpfile);
	return (fd);
}

bool	set_heredoc(t_parsed *parsed, t_envlist *lst)
{
	t_redirect	*red;
	int			file_count;

	file_count = 0;
	red = parsed->redirect;
	while (parsed != NULL)
	{
		while (red != NULL)
		{
			if (red->state == HERE_DOCUMENT)
			{
				file_count++;
				red->fd = create_heredoc_file(file_count, &red->tmpfile);
				if (red->fd == -1)
					return (false);
				if (my_heredoc(red, lst) != 0)
					return (false);
			}
			red = red->next;
		}
		if (parsed->next != NULL)
			red = parsed->next->redirect;
		parsed = parsed->next;
	}
	return (true);
}
