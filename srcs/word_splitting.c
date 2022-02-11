#include "word_splitting.h"
#include <stdio.h>
t_list	*word_splitting(char *str)
{
	t_list	splitted;
	size_t	index;
	size_t	length;
	char	*tmp;

	index = 0;
	length = 0;
	splitted.next = NULL;
	while (str[index] != '\0')
	{
		if (ft_strrchr(DELIMITER, str[index]))
		{
			if (length > 0)
			{
				tmp = ft_substr(str, index - length, length);
				if (tmp == NULL)
				{
					ft_putendl_fd("malloc failure", 2);
					exit(EXIT_FAILURE);
				}
				lstnew_add_back(&(splitted.next), tmp);
			}
			length = 0;
		}
		else
			length += 1;
		index += 1;
	}
	if (length > 0 && index != length)
	{
		tmp = ft_substr(str, index - length, length);
		if (tmp == NULL)
		{
			ft_putendl_fd("malloc failure", 2);
			exit(EXIT_FAILURE);
		}
		lstnew_add_back(&(splitted.next), tmp);
	}
	if (splitted.next == NULL)
		lstnew_add_back(&(splitted.next), str);
	return (splitted.next);
}
