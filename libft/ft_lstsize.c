/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyohei <wyohei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 13:40:58 by wyohei            #+#    #+#             */
/*   Updated: 2021/12/14 13:40:58 by wyohei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
int	ft_lstsize(t_list	*lst)
{
	int	i;

	i = 0;
	while (lst != NULL)
	{
		lst = lst -> next ;
		i++;
	}
	return (i);
}
