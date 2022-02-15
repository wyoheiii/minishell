/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkaneshi <tkaneshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 16:43:42 by tkaneshi          #+#    #+#             */
/*   Updated: 2022/02/15 16:28:00 by tkaneshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quote.h"

void	quote_remove(char *str, size_t start)
{
	size_t	index;

	index = start + 1;
	if (str[index] == '\0')
		str[start] = '\0';
	else
	{
		while (str[index] != '\0')
			str[start++] = str[index++];
		str[start] = '\0';
	}
}

static bool	check_close(t_expand *list, size_t index, char	ch)
{
	size_t	count;

	if (list->flag == NONE)
		return (true);
	count = index + 1;
	while (list->argv[count] != '\0')
	{
		if (list->argv[count] == ch)
			return (true);
		count += 1;
	}
	list->flag = NONE;
	return (false);
}

bool	set_quote_flag(t_expand *list, size_t index)
{
	if (list->flag == NONE && list->argv[index] == '\'')
		list->flag = SINGLE;
	else if (list->flag == NONE && list->argv[index] == '\"')
		list->flag = DOUBLE;
	else if (list->flag == SINGLE && list->argv[index] == '\'')
		list->flag = NONE;
	else if (list->flag == DOUBLE && list->argv[index] == '\"')
		list->flag = NONE;
	else
		return (false);
	if (!check_close(list, index, list->argv[index]))
		return (false);
	return (true);
}
