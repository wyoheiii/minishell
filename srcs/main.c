/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyohei <wyohei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 18:16:48 by wyohei            #+#    #+#             */
/*   Updated: 2022/02/12 20:19:56 by wyohei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expansion.h"

void	minishell(char **envp)
{
	char		*line;
	t_list		*token_list;
	t_parsed	*parsed;
	t_envlist	*lst;

	env_init(envp, &lst);
	catch_signal();
	while (1)
	{
		line = readline("minishell> ");
		if (line == NULL)
			break ;
		if (ft_strlen(line) == 0)
			continue ;
		add_history(line);
		token_list = lexer(line);
		parsed = parser(&token_list);
		expansion(parsed, lst);
		if (command_part(parsed, &lst) == EXIT)
			break ;
		free_parsed(&parsed);
		free(line);
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
