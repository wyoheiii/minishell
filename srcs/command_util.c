/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyohei <wyohei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 18:16:09 by wyohei            #+#    #+#             */
/*   Updated: 2022/02/12 20:00:08 by wyohei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_c.h"
char	*search_env_key_(const char *search, t_envlist *lst)
{
	while (lst != NULL)
	{
		if (ft_strncmp(search, lst->key, ft_strlen(search) + 1) == 0 \
		&& lst->value != NULL && lst->value[0] != '\0')
			return (lst->value);
		lst = lst->next;
	}
	return (NULL);
}

void	free_array(char **array)
{
	size_t	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	split_free(char **split)
{
	size_t	i;

	i = 0;
	while (split[i] != NULL)
	{
		free(split[i]);
		i++;
	}
	free(split);
}

int	command_size(char **arg)
{
	int	i;

	i = 0;
	while (arg[i] != NULL)
		i++;
	return (i);
}
