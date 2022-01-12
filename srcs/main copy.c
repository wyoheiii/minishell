#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"../inc/minishell_c.h"

int	aamain(int ac, char **av, char **envp)
{
	t_envlist *envlst;
	env_init(envp, &envlst);
	command_main(++av, envp,&envlst);
	(void)ac;
	return (0);
}