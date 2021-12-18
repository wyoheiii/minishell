#ifndef MINISHELL_C_H
#define MINISHELL_C_H
#include <stdio.h>
#include <unistd.h>
#include "../libft/libft.h"
#include <errno.h>
#include <string.h>
#include <stdbool.h>
void command_main(char **av,char **envp);
bool my_echo(char **command);
int my_pwd(void);
int my_exit(char **command);
#endif 