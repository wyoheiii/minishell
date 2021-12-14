#include "libft.h"
void	*ft_memchr(const void	*s, int	c, size_t	n)
{
	unsigned char	charr;
	unsigned char	*str;
	size_t			i;

	charr = (unsigned char)c;
	str = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (str[i] == charr)
			return ((void *)&str[i]);
		i++;
	}
	return (NULL);
}
