/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkaneshi <tkaneshi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 16:36:39 by wyohei            #+#    #+#             */
/*   Updated: 2022/02/22 21:35:45 by tkaneshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_c.h"

static void	word(char	**d, char	*s, char	c)
{
	size_t	i;

	i = 0;
	while (s[i] != c && s[i] != '\0')
	{
		i++;
	}
	if (i > 0)
		*d = ft_substr(s, 0, i);
	else
		*d = ft_strdup(".");
}

static int	return_split(char	**split, char	*s, char	c)
{
	size_t	i;
	size_t	j;
	size_t	cnt;

	i = 0;
	cnt = 0;
	while (ft_strlen(s) > i)
	{
		j = 0;
		while (s[i + j] != '\0' && s[i + j] != c)
			j++;
		word(&split[cnt], &s[i], c);
		if (split[cnt] == NULL)
			exit_error("malloc");
		i += j;
		cnt++;
		i++;
	}
	if (s[i - 1] == ':')
		split[cnt] = my_strdup(".");
	return (0);
}

char	**path_split(char const	*s, char	c)
{
	char	**split;
	size_t	size;
	size_t	i;

	if (s == NULL)
		return (NULL);
	size = 1;
	i = 0;
	while (s[i] != '\0')
	{
		if ((s[i] == c))
			size++;
		i++;
	}
	split = (char **)malloc(sizeof(char *) * (size + 1));
	if (split == NULL)
		return (NULL);
	if (return_split(split, (char *)s, c) == 1)
		return (NULL);
	split[size] = NULL;
	return (split);
}
