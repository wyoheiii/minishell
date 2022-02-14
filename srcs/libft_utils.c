/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkaneshi <tkaneshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 16:42:33 by tkaneshi          #+#    #+#             */
/*   Updated: 2022/02/14 16:42:34 by tkaneshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_utils.h"

char	*my_substr(char *str, size_t start, size_t length)
{
	char	*sub;

	sub = ft_substr(str, start, length);
	if (sub == NULL)
	{
		ft_putendl_fd("malloc failure", 2);
		exit(EXIT_FAILURE);
	}
	return (sub);
}

char	*my_strdup(char *str)
{
	char	*dup;

	if (str == NULL)
		return (NULL);
	dup = ft_strdup(str);
	if (dup == NULL)
	{
		ft_putendl_fd("malloc failure\n", 2);
		exit(EXIT_FAILURE);
	}
	return (dup);
}

char	*my_strjoin(char **s1, char **s2)
{
	char	*joined;

	joined = ft_strjoin(*s1, *s2);
	if (joined == NULL)
	{
		ft_putendl_fd("malloc failure", 2);
		exit(EXIT_FAILURE);
	}
	free(*s1);
	free(*s2);
	*s1 = NULL;
	*s2 = NULL;
	return (joined);
}

void	*my_calloc(size_t count, size_t size)
{
	void	*mem;

	mem = ft_calloc(count, size);
	if (mem == NULL)
	{
		ft_putendl_fd("malloc failure\n", 2);
		exit(EXIT_FAILURE);
	}
	return (mem);
}
