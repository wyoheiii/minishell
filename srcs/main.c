#include "minishell.h"
//extern int g_status;
void minishell(char **envp)
{
	char		*line;
	t_list		*token_list;
	t_parsed	*parsed;
	t_envlist   *lst;

	env_init(envp, &lst);
	while (1)
    {
        catch_signal();
        printf("[%d]", g_status);
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
        if (command_part(parsed, &lst) == EXIT) // 1でexit
             break ;
		free(line);
	}
    all_env_clear(&lst);
    free(line);
}

int	main(int ac, char **av, char **envp)
{
	extern int g_status;
	g_status = 0;
	(void)av;
	if(ac != 1)
		return (0);
	minishell(envp);
	printf("exit\n");
	return (0);
}