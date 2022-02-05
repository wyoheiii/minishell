#include "minishell_c.h"
int my_pwd(void)
{
    char *dir;

    dir = getcwd((char *)NULL, 0);
    //printf("pwd :%s\n",dir);
    if(!dir)
        perror("getcwd");
    else
    {
        printf("%s\n", dir);
        free(dir);
    }
    g_status = 0;
    return(0);
    //return(dir == NULL ? EXIT_FAILURE : EXIT_SUCCESS);
}