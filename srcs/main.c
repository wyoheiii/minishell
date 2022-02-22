/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyohei <wyohei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 18:16:48 by wyohei            #+#    #+#             */
/*   Updated: 2022/02/22 16:02:19 by wyohei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expansion.h"

int	set_command(t_envlist **lst, t_parsed *parsed, t_god *god)
{
	expansion(parsed, *lst);
	if (syntax_check(parsed) == -1)
		return (0);
	if (command_part(parsed, lst, god) == EXIT)
		return (EXIT);
	return (0);
}

void	god_set(t_god *god)
{
	god->pwd = getcwd(NULL, 0);
	god->oldpwd = NULL;
}

t_parsed	*pars(char *line)
{
	t_parsed	*parsed;
	t_list		*token_list;

	add_history(line);
	token_list = lexer(line);
	parsed = parser(&token_list);
	free(line);
	return (parsed);
}

void	minishell(char **envp)
{
	char		*line;
	t_parsed	*parsed;
	t_envlist	*lst;
	t_god		god;

	god_set(&god);
	env_init(envp, &lst);
	catch_signal();
	while (1)
	{
		line = readline("minishell> ");
		if (line == NULL)
			break ;
		if (ft_strlen(line) == 0)
		{
			free(line);
			continue ;
		}
		parsed = pars(line);
		if (set_command(&lst, parsed, &god) == EXIT)
			exit(g_status);
		free_parsed(&parsed);
	}
	ft_putendl_fd("exit", 2);
	exit(g_status);
}

int	main(int ac, char **av, char **envp)
{
	extern int	g_status;

	(void)av;
	g_status = 0;
	if (ac != 1)
		return (0);
	minishell(envp);
	return (0);
}
