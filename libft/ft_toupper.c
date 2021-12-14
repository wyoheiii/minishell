#include "libft.h"
int	ft_toupper(int	c)
{
	if (c >= 'a' && c <= 'z')
		c = c + 'A' - 'a';
	return (c);
}
