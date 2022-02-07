#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "lexer.h"
#include "parser.h"
#include "debug.h"

#include"../inc/minishell_c.h"

int	main(int ac, char **av, char **envp)
{
	char		*line;
	t_list		*token_list;
	t_parsed	*parsed;

	line = NULL;
	while (1)
	{
		line = readline("> ");
		if (line == NULL || strlen(line) == 0)
		{
			free(line);
			break ;
		}
		token_list = lexer(line);
		//print_token_list(token_list);
		parsed = parser(&token_list);
		//print_parsed(parsed);
		command_main(parsed->command, envp);
		add_history(line);
		free(line);
	}
	printf("exit\n");
	(void)ac;
	//execve("bin/bash", av, envp);
	return (0);
}
