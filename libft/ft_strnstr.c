/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyohei <wyohei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 13:42:35 by wyohei            #+#    #+#             */
/*   Updated: 2021/12/14 13:42:35 by wyohei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
char	*ft_strnstr(const char	*haystack, const char	*needle, size_t	len)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (haystack[i] != '\0' && len > i)
	{
		j = 0;
		while (haystack[i + j] == needle[j] && needle[j] != '\0' \
				&& haystack[i + j] != '\0' && len > j + i)
		{
			if (needle[j + 1] == '\0')
				return ((char *)&haystack[i]);
			j++;
		}
		i++;
	}
	if (needle[0] == '\0')
		return ((char *)haystack);
	return (NULL);
}
