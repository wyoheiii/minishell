/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_argv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkaneshi <tkaneshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 16:42:53 by tkaneshi          #+#    #+#             */
/*   Updated: 2022/02/14 16:42:54 by tkaneshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_argv.h"

static size_t	search_expand_char(t_expand *list, size_t index)
{
	while (list->argv[index] != '\0')
	{
		if (set_quote_flag(list, index))
			break ;
		if (list->flag != SINGLE && list->argv[index] == '$')
			break ;
		index += 1;
	}
	return (index);
}

static void	add_remaining(t_expand *new, t_expand *list)
{
	t_expand	*current;
	char		*str;
	size_t		length;

	length = ft_strlen(list->argv);
	if (list->checked < length)
	{
		str = my_substr(list->argv, list->checked, list->index);
		current = new;
		while (current->next != NULL)
			current = current->next;
		if (current->is_join)
			current->argv = my_strjoin(&(current->argv), &str);
		else
			expand_add_back(&new, expand_new(str));
	}
}

t_expand	*get_expanded(t_expand *list, t_envlist *envlist, bool *flag)
{
	t_expand	*tmp;

	*flag = true;
	tmp = expand_new(my_strdup(""));
	tmp->is_join = true;
	while (list->argv != NULL && list->argv[list->index] != '\0')
	{
		list->index = search_expand_char(list, list->index);
		if (is_remove(list))
			quote_remove(list->argv, list->index);
		else if (is_expand(list))
			*flag = add_expanded_param(tmp, list, envlist);
	}
	return (tmp);
}

t_expand	*expand_argv(t_expand *list, t_envlist *envlist)
{
	t_expand	new_list;
	t_expand	*tmp;
	bool		flag;

	new_list.next = NULL;
	while (list != NULL)
	{
		tmp = get_expanded(list, envlist, &flag);
		if (list->argv != NULL && (flag || tmp->argv[0] != '\0'))
		{
			add_remaining(tmp, list);
			expand_add_back(&(new_list.next), tmp);
		}
		else
			free_expand(&tmp);
		list = list->next;
	}
	return (new_list.next);
}
