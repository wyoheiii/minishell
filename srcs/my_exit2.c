/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_exit2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyohei <wyohei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 15:11:08 by wyohei            #+#    #+#             */
/*   Updated: 2022/02/21 16:41:11 by wyohei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_c.h"

static bool	exit_atoi2(char *str, int flag, size_t i, long long *num)
{
	long long	max;
	long long	one;

	max = (LLONG_MAX) / 10;
	one = (LLONG_MAX) % 10;
	while (str[i] != '\0')
	{
		if (i > 19)
			return (false);
		if (flag == 1 && (*num > max || (*num == max && (str[i] - '0' > one))))
			return (false);
		if (flag == -1 && (*num > max || \
		(*num == max && ((str[i] - '0') > one + 1))))
			return (false);
		*num = *num * 10 + str[i] - '0';
		i++;
	}
	*num = flag * ((long long)*num);
	return (true);
}

bool	exit_atoi(char *str, long long *num)
{
	int		flag;
	size_t	i;

	i = 0;
	flag = 1;
	if (str[0] == '+' || str[0] == '-')
	{
		if (str[0] == '-')
			flag = -1;
		i++;
	}
	while (str[i] == '0' && str[i] != '\0')
		i++;
	return (exit_atoi2(str, flag, i, num));
}
