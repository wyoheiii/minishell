/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyohei <wyohei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 13:41:41 by wyohei            #+#    #+#             */
/*   Updated: 2021/12/14 13:41:41 by wyohei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
char	*ft_strchr(const char	*s, int	c)
{
	char	charr;
	size_t	i;

	i = 0;
	charr = (char)c;
	while (s[i] != '\0')
	{
		if (s[i] == charr)
			return ((char *)&s[i]);
		i++;
	}
	if (charr == '\0')
		return ((char *)&s[i]);
	return (NULL);
}
