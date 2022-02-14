/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkaneshi <tkaneshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 16:42:36 by tkaneshi          #+#    #+#             */
/*   Updated: 2022/02/14 16:42:37 by tkaneshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list_utils.h"

t_list	*my_lstnew(void *content)
{
	t_list	*new_list;

	new_list = ft_lstnew(content);
	if (new_list == NULL)
	{
		ft_putendl_fd("malloc failure", 2);
		exit(EXIT_FAILURE);
	}
	return (new_list);
}

void	lstnew_add_back(t_list **lst, void *content)
{
	t_list	*new_list;

	new_list = my_lstnew(content);
	ft_lstadd_back(lst, new_list);
}
