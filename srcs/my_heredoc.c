/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyohei <wyohei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 18:17:29 by wyohei            #+#    #+#             */
/*   Updated: 2022/02/23 20:05:01 by wyohei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_c.h"

char	*expand_heredoc(char *line, t_envlist *envlist)
{
	t_expand	*expand;
	t_expand	*new;
	char		*ret;

	expand = expand_new(line);
	new = expand_argv(expand, envlist);
	free_expand(&expand);
	ret = my_strdup((new->argv));
	free_expand(&new);
	return (ret);
}

void	line_in_fd(int fd, t_redirect *redirect, t_envlist *lst, char *line)
{
	char	*expand;

	if (redirect->quote != 1)
	{
		expand = expand_heredoc(line, lst);
		ft_putendl_fd(expand, fd);
		free(expand);
	}
	else
	{
		ft_putendl_fd(line, fd);
		free(line);
	}
}

void	heredoc_child(int fd, t_redirect *redirect, t_envlist *lst)
{
	char	*line;

	while (1)
	{
		heredoc_sig();
		line = readline("> ");
		if (line == NULL)
			break ;
		if (ft_strncmp(line, redirect->filename, \
		ft_strlen(redirect->filename) + 1) == 0)
			break ;
		line_in_fd(fd, redirect, lst, line);
	}
	close(fd);
	free(line);
	exit(0);
}

int	heredoc_waitpid(pid_t pid, int *status, int option)
{
	if (waitpid(pid, status, option) < 0)
		exit_error("waitpid");
	if (*status)
	{
		g_status = WEXITSTATUS(*status);
		return (1);
	}
	return (0);
}

int	my_heredoc(t_redirect *redirect, t_envlist *lst)
{
	pid_t	pid;
	int		status;
	int		ret;

	ret = 0;
	pid = my_fork();
	if (pid == 0)
		heredoc_child(redirect->fd, redirect, lst);
	else
		ret = heredoc_waitpid(pid, &status, 0);
	if (ret)
		return (ret);
	return (ret);
}
