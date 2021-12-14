/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyohei <wyohei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 13:41:16 by wyohei            #+#    #+#             */
/*   Updated: 2021/12/14 13:41:16 by wyohei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
void	*ft_memset(void	*b, int	c, size_t	len)
{
	unsigned char	charr;
	unsigned char	*in_char;

	charr = (unsigned char)c;
	in_char = (unsigned char *)b;
	while (len > 0)
	{
		*in_char++ = charr;
		len--;
	}
	return (b);
}
