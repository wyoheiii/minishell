/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_is.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkaneshi <tkaneshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 16:42:56 by tkaneshi          #+#    #+#             */
/*   Updated: 2022/02/14 16:42:56 by tkaneshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_is.h"

bool	is_remove(t_expand *list)
{
	if (list->flag == NONE
		&& (list->argv[list->index] == '\''
			|| list->argv[list->index] == '\"'))
		return (true);
	else if (list->flag == SINGLE && list->argv[list->index] == '\'')
		return (true);
	else if (list->flag == DOUBLE && list->argv[list->index] == '\"')
		return (true);
	return (false);
}

bool	is_expand(t_expand *list)
{
	if (list->flag == DOUBLE && (list->argv[list->index] == '$'
			&& list->argv[list->index + 1] == '\"'))
		list->index += 1;
	else if ((list->argv[list->index] == '$'
			&& list->argv[list->index + 1] == '\0'))
		list->index += 1;
	else if (list->flag == NONE && (list->argv[list->index] == '$'
			&& list->argv[list->index + 1] == '"'))
		list->index += 1;
	else if (list->flag == NONE && (list->argv[list->index] == '$'
			&& list->argv[list->index + 1] == '"'))
		list->index += 1;
	else if (list->flag != SINGLE && (list->argv[list->index] == '$'
			&& list->argv[list->index + 1] != '\0'))
		return (true);
	return (false);
}
