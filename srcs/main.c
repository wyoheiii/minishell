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

int print_syntax_err(char *err)
{
    ft_putstr_fd("minishell: syntax error near unexpected token", 2);
    ft_putstr_fd("`",2);
    ft_putstr_fd(err,2);
    ft_putendl_fd("'",2);
    g_status = 2;
    return (-1);
}
int syntax_check2(t_parsed *parsed)
{
    if(parsed->redirect->filename == NULL && \
    ((parsed->redirect->state == REDIRECT_INPUT) || \
    (parsed->redirect->state == REDIRECT_OUTPUT) || \
    (parsed->redirect->state == REDIRECT_APPEND) || \
    (parsed->redirect->state == HERE_DOCUMENT)))
        return(print_syntax_err("newline"));
    return(0);
}
int syntax_check(t_parsed *parsed)
{
    int i =1;
    printf("parsed :%p\n",parsed);
    while (parsed != NULL)
    {
        printf("                          %d\n",i);
        printf("=====================================================\n");
        printf("parsed coma ;%p\n",parsed->command);
        printf("parsed redirect ;%p\n",parsed->redirect);
        printf("parsed coma ;%s\n",parsed->command[0]);
        printf("parsed filename ;%s\n",parsed->redirect->filename);
        printf("parse stas %d\n",parsed->state);
        printf("=====================================================\n");
        if((parsed->command[0] == NULL && parsed->redirect->filename == NULL\
        && parsed->state == PIPE) || (parsed->next == NULL && parsed->state == PIPE))
        {
            if(parsed->next != NULL) {
                if (parsed->next->command[0] == NULL && parsed->next->redirect->filename == NULL\
                        && parsed->next->state == PIPE)
                    return (print_syntax_err("||"));
            }
            return(print_syntax_err("|"));
        }
        if(parsed->redirect != NULL && syntax_check2(parsed) == -1) {
            printf("haitta\n");
            return (-1);
        }
        parsed = parsed->next;
        i++;
    }

    return(0);
}
int set_command(t_envlist **lst, t_parsed *parsed)
{
    if(syntax_check(parsed) == -1)
        return (0);
    expansion(parsed, *lst);
    if (command_part(parsed, lst) == EXIT)
        return (EXIT);
    return (0);
}
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
		if(set_command(&lst,parsed) == EXIT)
            break;
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
