#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"../inc/minishell_c.h"

int	aamain(int ac, char **av, char **envp)
{
	t_envlist *envlst;
	if(!env_init(envp, &envlst))
	{
		printf("malloc sippaisitayo!\n");
		return(false);
	}
	command_main(++av, envp,&envlst);
	(void)ac;
	return (0);
}