#include "libft.h"
void	ft_bzero(void	*s, size_t	len)
{
	unsigned char	*in_zero;
	size_t			i;

	i = 0;
	in_zero = (unsigned char *)s;
	while (i < len)
	{
		in_zero[i] = 0;
		i++;
	}
}
