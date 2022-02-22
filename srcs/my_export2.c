/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyohei <wyohei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 18:17:23 by wyohei            #+#    #+#             */
/*   Updated: 2022/02/21 15:11:38 by wyohei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_c.h"

int	print_export_env(t_envlist *lst)
{
	while (lst != NULL)
	{
        if(lst->key != NULL && lst->key[0] == '\0')
        {
            lst = lst->next;
            continue ;
        }
		if (lst->key != NULL && lst->value == NULL)
			printf("declare -x %s\n", lst->key);
		else
			printf("declare -x %s=%c%s%c\n", lst->key, '"', lst->value, '"');
		lst = lst->next;
	}
	g_status = 0;
	return (0);
}

bool	char_check(char *arg)
{
	size_t	i;

	i = 0;
	if (!is_alpha_(arg[0]))
		return (false);
	while (arg[i] != '\0')
	{
		if (!isenv(arg[i]))
			return (false);
		i++;
	}
	return (true);
}

bool	check_arg2(char *arg, size_t i)
{
	while (i > 0)
	{
		i--;
		if (!isenv(arg[i]))
			return (false);
	}
	return (true);
}

bool	check_arg(char *arg, int *join_flag)
{
	size_t	i;

	i = 0;
	if (!is_alpha_(arg[0]))
		return (false);
	while (arg[i] != '\0' && arg[i] != '=')
		i++;
	if (arg[i] == '=')
	{
		while (i > 0)
		{
			i--;
			if (i > 0 && arg[i] == '+')
			{
				*join_flag = 1;
				i--;
			}
			if (!isenv(arg[i]))
				return (false);
		}
		return (true);
	}
	else
		return (check_arg2(arg, i));
}

bool	key_match_check(char *arg, t_envlist *lst)
{
	size_t	key_size;
	char	*key;

	key = env_get_key(arg);
	key_size = ft_strlen(key);
	while (lst != NULL)
	{
		if (ft_strncmp(key, lst->key, key_size + 1) == 0)
		{
			free(key);
			return (true);
		}
		lst = lst->next;
	}
	free(key);
	return (false);
}
