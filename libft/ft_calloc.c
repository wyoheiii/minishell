#include "libft.h"
void	*ft_calloc(size_t	count, size_t	size)
{
	void	*zero;
	size_t	total;

	if (count == 0 || size == 0)
	{
		count = 1;
		size = 1;
	}
	if (size != 0 && count > SIZE_MAX / size)
		return (NULL);
	total = size * count;
	zero = malloc(count * size);
	if (zero == NULL)
		return (NULL);
	ft_bzero(zero, total);
	return (zero);
}

