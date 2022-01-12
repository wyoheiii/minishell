#include "minishell_c.h"
// bash-3.2$ export _=AA
// bash-3.2$ echo $?
// 0
// bash-3.2$ export _=AA
// bash-3.2$ echo $_
// _
int my_env(t_envlist *envlst)
{
    //=がないやつ
    // char *tmp;
    // char *dir;
    // dir = getcwd((char *)NULL, 0);
    // if(dir == NULL);
    while(envlst != NULL)
    {
        if(envlst->key[0] == '_' && envlst->key[1] != '\0')
        {
            //_=やらなくていいかも
            printf("wakaran\n");
        }
        else if(envlst->value[0] != '\0')
                printf("%s=%s\n", envlst->key, envlst->value);
        envlst = envlst->next;
    }
    return(1);
}
