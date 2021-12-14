/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyohei <wyohei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 13:39:56 by wyohei            #+#    #+#             */
/*   Updated: 2021/12/14 13:39:56 by wyohei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
static int	return_atoi(const char	*str, int	check, size_t	i)
{
	unsigned long	total;
	unsigned long	max_check;
	int				one;

	total = 0;
	max_check = (LONG_MAX) / 10;
	one = (LONG_MAX) % 10;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (total > max_check || (total == max_check && (str[i] - '0') > one))
		{
			if (check == 1)
				return ((int)LONG_MAX);
			if (check == -1)
				return ((int)LONG_MIN);
		}
		total = total * 10 + str[i] - '0';
		i++;
	}
	return ((int)total * check);
}

int	ft_atoi(const char	*str)
{
	size_t	i;
	int		check;

	check = 1;
	i = 0;
	while ((str[i] == ' ') || (str[i] == '\t') || (str[i] == '\n')
		|| (str[i] == '\v') || (str[i] == '\r') || (str[i] == '\f'))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			check = check * -1;
		i++;
	}
	return (return_atoi(str, check, i));
}
