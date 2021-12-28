#include "../inc/minishell_c.h"
//=の一個前までを入れる
//envpだとやばい場合がある setenvが呼ばれた場合に正しい動作をしない可能性があるのでexternを使ったほうがいいかも
bool    env_init(char **env, t_envlist **envlst)
{
    size_t i;
    t_envlist   *new;
    if(env)
        *envlst = env_new(env[0]);
    i = 1;
    while(env[i] != NULL)
    {
        if(env[i][0] == '_' && env[i][1] == '=')
        {
            i++;
            continue ;
        }
        new = env_new(env[i]);
        lstadd_back(envlst, new);
        i++;
    }
    new = env_new("OLDPWD");
    lstadd_back(envlst, new);
    return (true);
}
