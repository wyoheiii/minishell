#include "minishell_c.h"
//失敗が1成功が0
//bash: cd: lv03: No such file or directory
//同じディレクトリならこれ
//bash: cd: /Users/mkatou/: Permission denied
//bash: cd: HOME not set HOMEがなかったらこれ
//未テスト
// OLD PWD更新
// rm でカレントディレクトリ消した後にｃｄ．とか
int cd_error(char *error)
{
    if(error == NULL)
    {
        ft_putstr_fd("minishell: cd: HOME not set\n",2);
        g_status = 1;
        return (0);
    }
    else
    {
        g_status = 1;
        ft_putstr_fd("minishell: cd: ", 2);
        ft_putstr_fd(error, 2);
        //ft_putstr_fd(, 2);
        //ft_putstr_fd(, 2);
        return (0);
    }

}
int my_cd(char **command, t_envlist *lst)
{
    char *path;
    char *error;
    if(command[1] == NULL)
    {
        path = search_env_key_("HOME", lst);
        if(path == NULL)
            return (cd_error(NULL));
        if(chdir(path) != 0)
            perror("chdir");
    }
    else
    {
        if(chdir(command[1]) != 0)
        {
            error = ft_strjoin("minishell: cd: ",command[1]);
            if(error == NULL)
                exit(1);
            g_status = 1;
            perror(error);
        }
    }
    g_status = 0;
    return(0);
}