/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyohei <wyohei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 18:17:29 by wyohei            #+#    #+#             */
/*   Updated: 2022/02/12 20:17:17 by wyohei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell_c.h"

char	*expand_heredoc(char *line, t_envlist *envlist)
{
    t_expand	*expand;
    t_expand	*new;
    char *ret;

    expand = expand_new(line);
    new = expand_argv(expand, envlist);
    free_expand(&expand);
    ret = my_strdup((new->argv));
    free_expand(&new);
    return (ret);
}
void	heredoc_child(int pfd[2], t_redirect *redirect, t_envlist *lst)
{
	char	*line;
    char    *expand;
	my_close(pfd[0]);
	while (1)
	{
		heredoc_sig();
		line = readline("> ");
		if (line == NULL)
			break ;
		if (ft_strncmp(line, redirect->filename, \
        ft_strlen(redirect->filename) + 1) == 0)
			break ;
        if(redirect->quote != 1)
        {
            expand = expand_heredoc(line, lst);
            ft_putendl_fd(expand, pfd[1]);
            free(expand);
        }
        else
        {
            ft_putendl_fd(line, pfd[1]);
            free(line);
        }
	}
	free(line);
	my_close(pfd[1]);
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
	int		pfd[2];
	int		status;
	int		ret;

	ret = 0;
	my_pipe(pfd);
	pid = my_fork();
	if (pid == 0)
		heredoc_child(pfd, redirect, lst);
	else
		ret = heredoc_waitpid(pid, &status, 0);
	if (ret)
	{
		my_close(pfd[1]);
		my_close(pfd[0]);
		return (ret);
	}
	my_close(pfd[1]);
	redirect->fd = pfd[0];
	return (ret);
}

bool	set_heredoc(t_parsed *parsed, t_envlist *lst)
{
	t_redirect	*red;

	red = parsed->redirect;
	while (parsed != NULL)
	{
		while (red != NULL)
		{
			if (red->state == HERE_DOCUMENT)
			{
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
