#include "word_splitting.h"

static void	add_split_token(t_list **list, char *str,
	size_t start, size_t length)
{
	char	*token;

	if (length == 0)
		return ;
	token = ft_substr(str, start, length);
	if (token == NULL)
	{
		ft_putendl_fd("malloc failure", 2);
		exit(EXIT_FAILURE);
	}
	lstnew_add_back(list, token);
}

t_list	*word_splitting(char *str)
{
	t_list	splitted;
	size_t	index;
	size_t	length;

	index = 0;
	length = 0;
	splitted.next = NULL;
	while (str[index] != '\0')
	{
		if (ft_strrchr(DELIMITER, str[index]))
		{
			add_split_token(&(splitted.next), str, index - length, length);
			length = 0;
		}
		else
			length += 1;
		index += 1;
	}
	if (index != length)
		add_split_token(&(splitted.next), str, index - length, length);
	if (splitted.next == NULL)
		lstnew_add_back(&(splitted.next), str);
	return (splitted.next);
}
