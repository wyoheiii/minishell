#include "minishell_c.h"
//=より前
char *env_get_key(char *env)
{
    size_t  i;
    char *key;
    if(env)
    {
        i = 0;
        while(env[i] != '\0' && isenv(env[i]))
            i++;
        key = ft_substr(env, 0, i);
        if(!key)
        {
            perror("malloc");
            exit(1);
        }
        return (key);
    }
    return(NULL);

}
//=の後を入れる
char *env_get_value(char *env)
{
    char *tmp;
    char *value;
    if(env)
    {
        tmp = ft_strchr(env, '=');
        if(!tmp)
            value = ft_strdup("");
        else
            value = ft_strdup(++tmp);
        if(!value)
        {
            perror("malloc");
            exit(1);
        }
        return(value);
    }
    return (NULL);
}
t_envlist	*env_lstlast(t_envlist	*lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}
t_envlist   *env_new(char *envp)
{
    t_envlist *new;

    new = (t_envlist *)my_malloc(sizeof(t_envlist));
    if (!new)
        return (NULL);
    new->key = env_get_key(envp);
    new->value = env_get_value(envp);
   // new->num = num;
    new->next = NULL;
    return(new);
}