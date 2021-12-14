/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyohei <wyohei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 13:42:39 by wyohei            #+#    #+#             */
/*   Updated: 2021/12/14 13:42:39 by wyohei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
char	*ft_strrchr(const char	*s, int	c)
{
	size_t	i;
	char	charr;

	i = 0;
	charr = (char)c;
	while (s[i] != '\0')
		i++;
	while (i > 0)
	{
		if (s[i] == charr)
			return ((char *)&s[i]);
		i--;
	}
	if (s[i] == charr)
		return ((char *)&s[i]);
	return (NULL);
}
