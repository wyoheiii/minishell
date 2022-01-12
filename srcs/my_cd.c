#include "minishell_c.h"
//失敗が1成功が0
//bash: cd: lv03: No such file or directory
//同じディレクトリならこれ
//bash: cd: /Users/mkatou/: Permission denied
//bash: cd: HOME not set HOMEがなかったらこれ
//未テスト
// OLD PWD更新
// rm でカレントディレクトリ消した後にｃｄ．とか

int my_cd(char **command)
{
    char *error;

    if(command[1] == NULL)
    {
        if(chdir(getenv("HOME")) != 0)
        {
            //ft_strjoin("minishell: cd: ",);
            perror("bash : cd");
        }
        //printf("modoriti %d\n", i);
    }
    else
    {
        error = ft_strjoin("minishell: cd: ", command[1]);
        if(!error)
            return(2);
        if(chdir(command[1]) != 0)
            perror(error);
        free(error);
        //printf("modoriti %d\n", i);
    }
    return(1);
}