#include "minishell_c.h"
char *search_env_key_(const char *search, t_envlist *lst)
{
    while(lst != NULL)
    {
        if(ft_strncmp(search,lst->key, ft_strlen(search))== 0 \
        && lst->value[0] != '\0')
            return (lst->value);
        lst = lst->next;
    }
    return(NULL);
}
void split_free(char **split)
{
    size_t i;
    i = 0;
    while(split[i] != NULL)
    {
        free(split[i]);
        i++;
    }
    free(split);
}