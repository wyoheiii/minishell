/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyohei <wyohei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 13:40:41 by wyohei            #+#    #+#             */
/*   Updated: 2021/12/14 13:40:42 by wyohei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
void	ft_lstdelone(t_list	*lst, void	(*del)(void*))
{
	if (lst == NULL)
		return ;
	if (del != NULL)
		del(lst -> content);
	free(lst);
}
