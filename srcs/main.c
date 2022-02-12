/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyohei <wyohei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 18:16:48 by wyohei            #+#    #+#             */
/*   Updated: 2022/02/12 18:16:49 by wyohei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expansion.h"
//extern int g_status;
void minishell(char **envp)
{
	char		*line;
	t_list		*token_list;
	t_parsed	*parsed;
	t_envlist   *lst;

	env_init(envp, &lst);
//    while(lst != NULL)
//    {
//        printf("%s\n",lst->key);
//        lst= lst->next;
//    }
    catch_signal();
	while (1)
    {
        //printf("[%d]", g_status);
        line = readline("minishell> ");
        if (line == NULL)
            break ;
        if (ft_strlen(line) == 0)
            continue ;
        add_history(line);
        token_list = lexer(line);
        //print_token_list(token_list);
        parsed = parser(&token_list);
        //print_parsed(parsed);
        expansion(parsed,lst);
        if (command_part(parsed, &lst) == EXIT){

            break;
        } // 1でexit
        free_parsed(&parsed);
		    free(line);
	}
    //free_parsed(&parsed);
    //all_env_clear(&lst);
    //free(line);
    ft_putendl_fd("exit",2);
    exit(g_status);
}

int ft_launch_minishell(char *argv,char **envp)
{
    t_envlist   *lst;
    t_list		*token_list;
	t_parsed	*parsed;
	env_init(envp, &lst);
    token_list = lexer(argv);
    //print_token_list(token_list);
    parsed = parser(&token_list);
    //print_parsed(parsed);
    command_part(parsed, &lst);
    return(g_status);
}

int	main(int ac, char **av, char **envp)
{
	extern int g_status;
	g_status = 0;

    if (ac >= 3 && !ft_strncmp(av[1], "-c",3))
    {
        int exit_status = ft_launch_minishell(av[2],envp);
        exit(exit_status);
    }
	if(ac != 1)
		return (0);
	minishell(envp);
	//printf("exit\n");
	return (0);
}