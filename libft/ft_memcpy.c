#include "libft.h"
void	*ft_memcpy(void	*dst, const void	*src, size_t	n)
{
	unsigned char		*d;
	unsigned const char	*s;
	size_t				i;

	d = (unsigned char *)dst;
	s = (unsigned const char *)src;
	i = 0;
	if (d == s)
		return (d);
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dst);
}
