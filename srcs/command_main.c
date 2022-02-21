/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyohei <wyohei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 15:57:41 by watanabeyou       #+#    #+#             */
/*   Updated: 2022/02/21 15:59:57 by wyohei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_c.h"

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

void	god_parsed_set(t_god *god, t_parsed *parsed)
{
	god->parsed = parsed;
}

int	command_part(t_parsed *parsed, t_envlist **lst, t_god *god)
{
	t_pipe	p;
	int		pipe_count;
	int		i;

	if (parsed == NULL)
		return (0);
	god_parsed_set(god, parsed);
	if (!set_heredoc(god->parsed, *lst))
		return (0);
	pipe_count = count_pipe(god->parsed);
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
