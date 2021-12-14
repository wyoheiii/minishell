/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyohei <wyohei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 13:42:43 by wyohei            #+#    #+#             */
/*   Updated: 2021/12/14 13:42:43 by wyohei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
static int	check(char	s1, char const	*set)
{
	size_t	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (s1 == set[i])
			return (1);
		i++;
	}
	if (s1 == '\0')
		return (1);
	return (0);
}

static char	*trimru(char	*str, char const	*s1, size_t	i, size_t	j)
{
	size_t	k;

	k = 0;
	while (i < j)
	{
		str[k] = s1[i];
		k++;
		i++;
	}
	str[k] = '\0';
	return (str);
}

char	*ft_strtrim(char const	*s1, char const	*set)
{
	char	*str;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (s1 == NULL || set == NULL)
		return (NULL);
	while (s1[j] != '\0')
		j++;
	while (s1[i] != '\0' && check(s1[i], set) == 1)
		i++;
	while (j > i && check(s1[j - 1], set) == 1)
		j--;
	str = (char *)malloc(sizeof(char) * (j - i + 1));
	if (str == NULL)
		return (NULL);
	return (trimru(str, s1, i, j));
}
