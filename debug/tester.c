#include <stdio.h>
#include <stdlib.h>

#include "parser.h"
#include "lexer.h"
#include "debug.h"
#include "expansion.h"
#include"../inc/minishell_c.h"

#define BUF_SIZE 255

char	**g_env;

void	test_command(char *command)
{
	t_list		*token_list;
	t_parsed	*parsed;
	size_t		index;

	printf("  COMMAND>\x1b[1m\x1b[35m%s\x1b[39m\x1b[0m\n", command);
	fflush(stdout);
	printf("     bash>\x1b[1m\x1b[32m");
	fflush(stdout);
	system(command);
	printf("\x1b[39m\x1b[0m");
	fflush(stdout);
	token_list = lexer(command);
	if (token_list == NULL)
		printf("lexer return NULL\n");
	parsed = parser(&token_list);
	if (parsed == NULL)
		printf("parser return NULL\n");
	printf("minishell>\x1b[1m\x1b[31m");
	fflush(stdout);
	expansion(parsed);
	command_main(parsed->command, g_env);
	printf("\x1b[39m\x1b[0m");
	fflush(stdout);
	printf("------------------------\n");
}

// bashで実行して
int	main(int ac, char **av, char **envp)
{
	g_env = envp;

	test_command("echo test");
	test_command("echo $SHELL");
	test_command("echo $SHELL $SHELL");
	test_command("echo \"$SHELL\"");
	test_command("echo \'$SHELL\'");
	test_command("echo \"$SHELL $SHELL\"");
	test_command("echo \'$SHELL $SHELL\'");
}
