/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkaneshi <tkaneshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 16:43:04 by tkaneshi          #+#    #+#             */
/*   Updated: 2022/02/14 16:43:05 by tkaneshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_struct.h"

t_expand	*expand_new(char *argv)
{
	t_expand	*new;

	new = (t_expand *)malloc(sizeof(t_expand));
	if (new == NULL)
	{
		ft_putendl_fd("malloc failure", 2);
		exit(EXIT_FAILURE);
	}
	new->argv = argv;
	new->flag = NONE;
	new->is_join = false;
	new->index = 0;
	new->checked = 0;
	new->next = NULL;
	return (new);
}

void	expand_add_back(t_expand **head, t_expand *new)
{
	t_expand	*current;

	if (*head == NULL)
	{
		*head = new;
		return ;
	}
	current = *head;
	while (current->next != NULL)
		current = current->next;
	current->next = new;
}

size_t	expand_lst_size(t_expand *argv_list)
{
	t_expand	*tmp;
	size_t		size;

	tmp = argv_list;
	size = 0;
	while (tmp != NULL)
	{
		size += 1;
		tmp = tmp->next;
	}
	return (size);
}

void	free_expand(t_expand **expand)
{
	t_expand	*tmp;

	tmp = *expand;
	while ((*expand) != NULL)
	{
		tmp = (*expand);
		(*expand) = (*expand)->next;
		free (tmp->argv);
		free (tmp);
	}
}

t_expand	*convert_list(char **command)
{
	t_expand	*new;
	t_expand	*tmp;
	size_t		size;
	size_t		index;

	size = 0;
	while (command[size] != NULL)
		size += 1;
	index = 0;
	new = expand_new(command[index++]);
	if (new == NULL)
	{
		ft_putendl_fd("malloc failure", 2);
		exit(EXIT_FAILURE);
	}
	while (index < size)
	{
		tmp = expand_new(command[index++]);
		expand_add_back(&new, tmp);
	}
	return (new);
}
