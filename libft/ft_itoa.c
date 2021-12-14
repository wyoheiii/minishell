#include "libft.h"
static int	count(long	long	n)
{
	long	i;

	i = 0;
	if (n == 0)
	{
		i = 1;
		return (i);
	}
	if (n < 0)
	{
		n = n * -1;
		i++;
	}
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static void	return_itoa(int	i, long	long	long_n, char	*str)
{
	str[i--] = '\0';
	if (long_n == 0)
	{
		str[0] = '0';
		return ;
	}
	if (long_n < 0)
	{
		str[0] = '-';
		long_n = long_n * -1;
	}
	while (long_n > 0)
	{
		str[i] = long_n % 10 + '0';
		long_n = long_n / 10;
		i--;
	}
}

char	*ft_itoa(int	n)
{
	char		*str;
	long long	long_n;
	int			i;

	long_n = (long)n;
	i = count(long_n);
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (str == NULL)
		return (NULL);
	return_itoa(i, long_n, str);
	return (str);
}
