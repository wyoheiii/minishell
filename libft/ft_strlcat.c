/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyohei <wyohei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 13:42:01 by wyohei            #+#    #+#             */
/*   Updated: 2021/12/14 13:42:01 by wyohei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
size_t	ft_strlcat(char	*dst, const char	*src, size_t	dstsize)
{
	size_t	i;
	size_t	cnt;
	size_t	d_len;
	size_t	s_len;
	size_t	total;

	d_len = ft_strlen(dst);
	s_len = ft_strlen(src);
	total = d_len + s_len;
	cnt = dstsize - d_len - 1;
	i = 0;
	if (d_len < dstsize)
	{
		while (src[i] != '\0' && i < cnt)
			dst[d_len++] = src[i++];
		dst[d_len] = '\0';
		return (total);
	}
	dst[d_len] = '\0';
	return (s_len + dstsize);
}
