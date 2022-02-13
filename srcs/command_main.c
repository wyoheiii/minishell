/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyohei <wyohei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 15:57:41 by watanabeyou       #+#    #+#             */
/*   Updated: 2022/02/12 19:08:41 by wyohei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_c.h"

void	exec_error(char *command, t_envlist *lst)
{
    (void)lst;
    if (errno == 2)
    {
        ft_putstr_fd("minishell: ", 2);
        ft_putstr_fd(command, 2);
        ft_putstr_fd(": ", 2);
        ft_putendl_fd("command not found", 2);
        //ft_putendl_fd(strerror(errno), 2);
        exit(127);
    }
    if (errno == 8)
    {
        ft_putstr_fd("minishell: ", 2);
        ft_putstr_fd(command, 2);
        ft_putstr_fd(": ", 2);
        ft_putendl_fd(strerror(errno), 2);
        exit(127);
    }
    if (errno)
    {
        ft_putstr_fd("minishell: ", 2);
        ft_putstr_fd(command, 2);
        ft_putstr_fd(": ", 2);
        ft_putendl_fd(strerror(errno), 2);
        exit(126);
    }
}

int	count_pipe(t_parsed *parsed)
{
	int	ret;

	ret = 0;
	while (parsed != NULL)
	{
		if (parsed->state == PIPE)
			ret++;
		parsed = parsed->next;
	}
	return (ret);
}

bool	redirect_check(t_parsed *parsed)
{
	if (parsed->redirect != NULL)
	{
		if (parsed->redirect->state == REDIRECT_APPEND)
			return (true);
		if (parsed->redirect->state == REDIRECT_OUTPUT)
			return (true);
		if (parsed->redirect->state == REDIRECT_INPUT)
			return (true);
		if (parsed->redirect->state == HERE_DOCUMENT)
			return (true);
	}
	return (false);
}

void	god_init(t_god *god, t_parsed *parsed)
{
	god->parsed = parsed;
	god->pwd = NULL;
}

int	command_part(t_parsed *parsed, t_envlist **lst)
{
	t_god	god;
	t_pipe	p;
	int		pipe_count;
	int		i;

    if (parsed == NULL)
        return (0);
	god_init(&god, parsed);
	if (!set_heredoc(god.parsed))
		return (0);
	pipe_count = count_pipe(god.parsed);
	if (pipe_count == 0)
		return (single_command(god, lst));
    catch_sasenai_signal();
	pipe_init(&p, pipe_count);
	multi_command(p, lst, god, pipe_count);
	i = -1;
	command_sig();
	while (++i < pipe_count + 1)
		waitpid_get_status(p.pid[i], &p.status, 0);
	free(p.pipe_fd);
	free(p.pid);
	return (0);
}
