/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyohei <wyohei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 16:36:39 by wyohei            #+#    #+#             */
/*   Updated: 2022/02/21 16:38:51 by wyohei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_c.h"

static int	error(char	**split, size_t	cnt)
{
	size_t	i;

	i = 0;
	while (i < cnt)
	{
		free(split[i]);
		i++;
	}
	free(split);
	return (1);
}

static void	word(char	*d, char	*s, char	c)
{
	size_t	i;

	i = 0;
	while (s[i] != c && s[i] != '\0')
	{
		d[i] = s[i];
		i++;
	}
	d[i] = '\0';
}

static int	return_split(char	**split, char	*s, char	c)
{
	size_t	i;
	size_t	j;
	size_t	cnt;

	i = 0;
	cnt = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c || s[i] == '\0')
			i++;
		else
		{
			j = 0;
			while (s[i + j] != c && s[i + j] != '\0')
				j++;
			split[cnt] = (char *)malloc(sizeof(char) * (j + 1));
			if (split[cnt] == NULL)
				return (error(split, cnt));
			word(split[cnt], &s[i], c);
			i += j;
			cnt++;
		}
	}
	return (0);
}

char	**path_split(char const	*s, char	c)
{
	char	**split;
	size_t	size;
	size_t	i;

	if (s == NULL)
		return (NULL);
	size = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if ((s[i + 1] == c || s[i + 1] == '\0') && s[i] != c && s[i] != '\0')
			size++;
		i++;
	}
	split = (char **)malloc(sizeof(char *) * (size + 2));
	if (split == NULL)
		return (NULL);
	if (return_split(split, (char *)s, c) == 1)
		return (NULL);
	split[size + 1] = 0;
	split[size] = my_strdup(".");
	return (split);
}
