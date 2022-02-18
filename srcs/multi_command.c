/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyohei <wyohei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 18:16:51 by wyohei            #+#    #+#             */
/*   Updated: 2022/02/15 15:29:13 by wyohei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_c.h"

void	select_command(t_god *god, t_envlist **lst)
{
	if (builtin_select(god->parsed->command))
	{
		single_builtin(god, lst);
		exit(g_status);
	}
	if (redirect_check(god->parsed))
		if (select_redirect(god->parsed->redirect) == -1)
			exit(g_status);
	check_period(god->parsed);
	set_exec(god, lst);
}

void	multi_pipe(int (*pipe_fd)[2], int i, int pipe_count)
{
	if (i == 0)
	{
		my_dup2(pipe_fd[i][1], 1);
		my_close(pipe_fd[i][0]);
		my_close(pipe_fd[i][1]);
	}
	else if (i == pipe_count)
	{
		my_dup2(pipe_fd[i - 1][0], 0);
		my_close(pipe_fd[i - 1][0]);
		my_close(pipe_fd[i - 1][1]);
	}
	else
	{
		my_dup2(pipe_fd[i - 1][0], 0);
		my_dup2(pipe_fd[i][1], 1);
		my_close(pipe_fd[i - 1][0]);
		my_close(pipe_fd[i - 1][1]);
		my_close(pipe_fd[i][0]);
		my_close(pipe_fd[i][1]);
	}
}

void	pipe_init(t_pipe *p, int pipe_count)
{
	p->pipe_fd = my_malloc(sizeof(int *) * (pipe_count + 1));
	p->pid = my_malloc(sizeof(int) * (pipe_count + 1));
}

void	multi_command(t_pipe pipe, t_envlist **lst, t_god *god, int pipe_count)
{
	int	i;

	i = 0;
	catch_signal();
	while (god->parsed != NULL)
	{
		if (i != pipe_count && god->parsed->state == PIPE)
			my_pipe(pipe.pipe_fd[i]);
		catch_no_signal();
		pipe.pid[i] = my_fork();
		if (pipe.pid[i] == 0)
		{
			multi_pipe(pipe.pipe_fd, i, pipe_count);
			select_command(god, lst);
		}
		else if (i > 0)
		{
			my_close(pipe.pipe_fd[i - 1][0]);
			my_close(pipe.pipe_fd[i - 1][1]);
		}
		i++;
		god->parsed = god->parsed->next;
	}
}
