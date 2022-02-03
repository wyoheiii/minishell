#include "word_splitting.h"

t_list	*word_splitting(char *str)
{
	t_list	*splitted;
	size_t	index;
	size_t	length;

	index = 0;
	length = 0;
	splitted = NULL;
	while (str[index] != '\0')
	{
		if (ft_strrchr(DELIMITER, str[index]))
		{
			if (length > 0)
				lstnew_add_back(&splitted,
					my_substr(str, index - length, length));
			length = 0;
		}
		else
			length += 1;
		index += 1;
	}
	return (splitted);
}
