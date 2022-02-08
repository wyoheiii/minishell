#include "minishell_c.h"
//bash-3.2$ unset AAA=
//bash: unset: `AAA=': not a valid identifier
//記号があったらエラー、英字の連続なら問題ないキーの左側と一致したら削除
// export 単体のOLDPWDはどっからもってくるのか
//bash の cd - と 環境変数 OLDPWD
//cd したら oldpwd追加
//_=/usr/bin/env
// =がなくてもkeyに保存　envは=あるやつだけ出力
//_=は最後に使用した実行ファイルを表示
//ex

int	isenv(int	c)
{
	if ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z')
		|| (c >= 'a' && c <= 'z') || c == '_' )
		return (1);
	return (0);
}

int is_alpha_(int c)
{
    if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_')
		return (1);
	return (0);
}

int print_export_env(t_envlist *lst)
{
    while(lst != NULL)
    {
        //_= igai
        //printf("a\n");
        if(lst->key[0] == '_' && lst->key[1] != '\0')
        {
            lst = lst->next;
            continue;
        }
        if(lst->key != NULL && lst->value == NULL) {
            //printf("key%s\n",lst->key);
            printf("declare -x %s\n", lst->key);
//        else if(lst->value[0] != '\0')
        }
        else
            printf("declare -x %s=%c%s%c\n",lst->key, '"', lst->value, '"');
//        else
//            printf("declare -x %s\n",lst->key);
        lst = lst->next;
    }
    g_status = 0;
    return (0);
}

bool char_check(char *arg)
{
    size_t i;
    i = 0;

    if(!is_alpha_(arg[0]))
            return (false);
    while(arg[i] != '\0')
    {
        if(!isenv(arg[i]))
            return(false);
        i++;
    }
    return(true);
}
bool check_arg2(char *arg, size_t i)
{
    while(i > 0)
    {
        i--;
        if(!isenv(arg[i]))
            return(false);
    }
    return(true);
}
bool check_arg(char *arg,int *join_flag)
{
    size_t i;

    i = 0;
    if(!is_alpha_(arg[0]))
        return(false);
    while(arg[i] != '\0' && arg[i] != '=')
        i++;
    if(arg[i] == '=')
    {
        while(i > 0)
        {
            i--;
            if(i > 0 && arg[i] == '+')
            {
                *join_flag = 1;
                i--;
            }
            if(!isenv(arg[i]))
                return(false);
        }
        return(true);
    }
    else
        return(check_arg2(arg, i));
    //return(true);
}

bool key_match_check(char *arg, t_envlist *lst)
{
    size_t key_size;
    char *key;

    key = env_get_key(arg);
    key_size = ft_strlen(key);
    while(lst != NULL)
    {
        if(ft_strncmp(key, lst->key, key_size + 1) == 0)
            return (true);
        lst = lst->next;
    }
    free(key);
    return(false);
}

void join_value(char *arg, t_envlist **lst)
{
    size_t key_size;
    char *value;
    char *key;
    t_envlist *top;

    key = env_get_key(arg);
    value = env_get_value(arg);
    key_size = ft_strlen(key);
    top = *lst;
    while(*lst != NULL)
    {
        if(ft_strncmp(key,(*lst)->key, key_size + 1) == 0)
        {
            (*lst)->value = my_strjoin(&(*lst)->value, &value);
            *lst = top;
            return ;
        }
        *lst = (*lst)->next;
    }
}

void dup_value(char *arg, t_envlist **lst)
{
    size_t key_size;
    char *tmp;
    char *key;
    t_envlist *top;

    key = env_get_key(arg);
    key_size = ft_strlen(key);
    top = *lst;
    while(*lst != NULL)
    {
        if(ft_strncmp(key,(*lst)->key, key_size + 1) == 0)
        {
            tmp = env_get_value(arg);
            free((*lst)->value);
            (*lst)->value = tmp;
            *lst = top;
            return ;
        }
        *lst = (*lst)->next;
    }
}

bool set_key_value(char *arg, t_envlist **lst)
{

    int join_flag;
    t_envlist *new;

    join_flag = 0;
    if(check_arg(arg, &join_flag))
    {
        if (key_match_check(arg, *lst))
        {
            if(join_flag)
                join_value(arg, lst);
            else
                dup_value(arg, lst);
        }
        else
        {
            new = env_new(arg);
            lstadd_back(lst,new);
        }
        return(true);
    }
    return(false);
}
void export_error(char *error)
{
    //printf("minishell: export: `%s': not a valid identifier\n",arg[i]);
    ft_putstr_fd("minishell: export: `",2);
    ft_putstr_fd(error,2);
    ft_putstr_fd("': not a valid identifier\n",2);
    g_status = 1;
}

int my_export(char **arg, t_envlist **lst)
{
    int error_flag;
    size_t  i;
    int ret_flag;
    ret_flag = 0;
    if(arg[1] == NULL)
        return(print_export_env(*lst));
    else
    {
        error_flag = 0;
        i = 1;
        while(arg[i] != NULL)
        {
//            if(char_check(arg[i]))
//            {
//                printf("damedatta\n");
//                i++;
//                continue;
//            }
            if(!set_key_value(arg[i], lst))
            {
                ret_flag = 1;
                error_flag = 1;
            }
            if(error_flag)
                export_error(arg[i]);
            error_flag = 0;
            i++;
        }
    }
    if(!ret_flag)
        g_status = 0;
    return(0);
    // while(*lst)
    // {
    //     printf("%s=%s\n", (*lst)->key,(*lst)->value);
    //     *lst = (*lst)->next;
    // }
    return(0);
    //失敗が１
}