/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyohei <wyohei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 13:42:31 by wyohei            #+#    #+#             */
/*   Updated: 2021/12/14 13:42:31 by wyohei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
int	ft_strncmp(const char	*s1, const char	*s2, size_t	n)
{
	size_t			i;
	unsigned char	*dest;
	unsigned char	*src;

	i = 0;
	dest = (unsigned char *)s1;
	src = (unsigned char *)s2;
	if (n == 0)
		return (0);
	while (dest[i] != '\0' && src[i] != '\0' && i < n - 1 && dest[i] == src[i])
		i++;
	return (dest[i] - src[i]);
}
