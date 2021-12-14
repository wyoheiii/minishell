#include "libft.h"
char	*ft_strdup(const char	*s1)
{
	size_t	i;
	size_t	j;
	char	*str;

	i = 0;
	j = 0;
	while (s1[j] != '\0')
		j++;
	str = (char *)malloc(sizeof(char) * (j + 1));
	if (str == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
