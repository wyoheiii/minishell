/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyohei <wyohei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 13:40:01 by wyohei            #+#    #+#             */
/*   Updated: 2021/12/14 13:40:01 by wyohei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
void	ft_bzero(void	*s, size_t	len)
{
	unsigned char	*in_zero;
	size_t			i;

	i = 0;
	in_zero = (unsigned char *)s;
	while (i < len)
	{
		in_zero[i] = 0;
		i++;
	}
}
