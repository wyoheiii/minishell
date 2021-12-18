#include "../inc/minishell_c.h"
int my_pwd(void)
{
    char *dir;

    dir = getcwd((char *)NULL, 0);
    if(!dir)
        perror("getcwd");
    else
    {
        printf("%s",dir);
        free(dir);
    }
    return(dir == NULL ? EXIT_FAILURE : EXIT_SUCCESS);
}