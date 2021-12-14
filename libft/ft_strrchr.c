#include "libft.h"
char	*ft_strrchr(const char	*s, int	c)
{
	size_t	i;
	char	charr;

	i = 0;
	charr = (char)c;
	while (s[i] != '\0')
		i++;
	while (i > 0)
	{
		if (s[i] == charr)
			return ((char *)&s[i]);
		i--;
	}
	if (s[i] == charr)
		return ((char *)&s[i]);
	return (NULL);
}
