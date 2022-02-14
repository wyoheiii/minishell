/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkaneshi <tkaneshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 16:43:42 by tkaneshi          #+#    #+#             */
/*   Updated: 2022/02/14 16:43:42 by tkaneshi         ###   ########.fr       */
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
	return (true);
}
