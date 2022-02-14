/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_param.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkaneshi <tkaneshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 16:43:00 by tkaneshi          #+#    #+#             */
/*   Updated: 2022/02/14 21:14:14 by tkaneshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_param.h"

void	expand_join_last(t_expand *new, char *str)
{
	char	*tmp;

	while (new->next != NULL)
		new = new->next;
	if (new->argv == NULL)
		new->argv = ft_strdup(str);
	else
	{
		tmp = ft_strjoin((new->argv), str);
		free(new->argv);
		new->argv = tmp;
	}
}

void	expand_joinflag_on(t_expand *new)
{
	while (new->next != NULL)
		new = new->next;
	new->is_join = true;
}

void	expand_add_split(t_expand *new, char *param)
{
	t_list	*split;
	t_list	*tmp;

	split = word_splitting(param);
	if (split == NULL)
		split = ft_lstnew(param);
	if (!ft_isspace(param[0]) || new->argv[0] == '\0')
	{
		tmp = split;
		expand_join_last(new, (char *)tmp->content);
		split = split->next;
		free(tmp->content);
		free(tmp);
	}
	while (split != NULL)
	{
		tmp = split;
		expand_add_back(&new, expand_new(tmp->content));
		split = split->next;
		free(tmp);
	}
}

bool	add_expanded_param(t_expand *new, t_expand *list, t_envlist *envlist)
{
	char	*str;
	char	*param;

	if (list->index != list->checked)
	{
		str = my_substr(list->argv, list->checked,
				(list->index - list->checked));
		expand_join_last(new, str);
		free (str);
	}
	param = param_func(list, envlist);
	list->checked = list->index;
	if (param == NULL && list->flag == DOUBLE)
		return (true);
	else if (param == NULL)
		return (false);
	if (list->flag == NONE)
		expand_add_split(new, param);
	else
		expand_join_last(new, param);
	if (!ft_isspace(param[ft_strlen(param) - 1]))
		expand_joinflag_on(new);
	free(param);
	return (true);
}
