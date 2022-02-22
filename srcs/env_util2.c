/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_util2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyohei <wyohei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 18:16:25 by wyohei            #+#    #+#             */
/*   Updated: 2022/02/22 20:47:12 by wyohei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_c.h"

char	*env_get_key(char *env)
{
	size_t	i;
	char	*key;

	if (env)
	{
		i = 0;
		while (env[i] != '\0' && isenv(env[i]))
			i++;
		key = ft_substr(env, 0, i);
		if (!key)
			exit_error("malloc");
		return (key);
	}
	return (NULL);
}

char	*env_get_value(char *env)
{
	char	*tmp;
	char	*value;

	if (env)
	{
		tmp = ft_strchr(env, '=');
		if (!tmp)
			value = NULL;
		else if (tmp[1] == '\0')
			value = my_strdup("");
		else
			value = my_strdup(++tmp);
		return (value);
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

t_envlist	*env_new(char *envp)
{
	t_envlist	*new;

	new = (t_envlist *)my_malloc(sizeof(t_envlist));
	if (!new)
		exit_error("malloc");
	new->key = env_get_key(envp);
	new->value = env_get_value(envp);
	new->next = NULL;
	return (new);
}

bool	check_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}
