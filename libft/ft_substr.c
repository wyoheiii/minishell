#include "libft.h"
char	*ft_substr(char const	*s, unsigned int	start, size_t	len)
{
	char	*str;
	size_t	i;
	size_t	str_len;

	i = 0;
	if (s == NULL)
		return (NULL);
	str_len = ft_strlen(s);
	if (str_len < start)
		return (ft_strdup(""));
	if (str_len < start + len)
		len = str_len - start;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	while (s[i] != '\0' && i < len)
		str[i++] = s[start++];
	str[i] = '\0';
	return (str);
}
