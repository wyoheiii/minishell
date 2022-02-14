/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkaneshi <tkaneshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 16:43:54 by tkaneshi          #+#    #+#             */
/*   Updated: 2022/02/14 16:43:55 by tkaneshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	lstdel_front(t_list **lst)
{
	t_list		*tmp;

	tmp = (*lst)->next;
	free((*lst)->content);
	free((*lst));
	(*lst) = tmp;
}

bool	ft_isspace(char ch)
{
	if ((ch >= '\a' && ch <= '\r') || ch == ' ')
		return (true);
	return (false);
}
