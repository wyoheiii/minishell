/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyohei <wyohei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 18:16:21 by wyohei            #+#    #+#             */
/*   Updated: 2022/02/12 19:25:07 by wyohei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_c.h"
void	env_delone(t_envlist *lst)
{
	if (!lst)
		return ;
	if (lst->value)
	{
		free(lst->value);
	}
	if (lst->key)
	{
		free(lst->key);
	}
	if (lst)
		free(lst);
}

void	all_env_clear(t_envlist **lst)
{
	t_envlist	*tmp;

	if (!lst)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		env_delone(*lst);
		*lst = tmp;
	}
	*lst = NULL;
}

void	lstadd_back(t_envlist **lst, t_envlist *new)
{
	t_envlist	*tmp;

	if (!lst)
		return ;
	if (*lst)
	{
		tmp = env_lstlast(*lst);
		tmp->next = new;
	}
	else
		*lst = new;
}

void	lst_add_front(t_envlist **lst, t_envlist *new)
{
	if (!new || !lst)
		return ;
	new -> next = *lst;
	*lst = new;
}

size_t	env_lst_size(t_envlist *lst)
{
	size_t	i;

	i = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}
