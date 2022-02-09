#include "word_splitting.h"

t_list	*word_splitting(char *str)
{
	t_list	*splitted;
	size_t	index;
	size_t	length;
	char	*tmp;

	index = 0;
	length = 0;
	splitted = NULL;
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
				lstnew_add_back(&splitted, tmp);
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
		lstnew_add_back(&splitted, tmp);
	}
	lstnew_add_back(&splitted, NULL);
	return (splitted);
}

bool	is_connect_prev(char *argv)
{
	if (argv == NULL)
		return (false);
	if (!ft_isspace(argv[0]))
		return (true);
	return (false);
}

bool	is_connect_next(char *argv)
{
	if (argv == NULL || ft_strlen(argv) == 0)
		return (false);
	if (!ft_isspace(argv[ft_strlen(argv) - 1]))
		return (true);
	return (false);
}

char	*func(t_expand **list, char **line, t_list *split)
{
	t_list		*tmp;
	t_expand	*new;
	t_expand	*next;

	if (split == NULL)
		return (*line);
	tmp = split;
	if (is_connect_prev(tmp->content))
	{
		(*line) = ft_strjoin(*line, tmp->content);
		(*list)->argv = (*line);
		tmp = tmp->next;
	}
	while (tmp->next != NULL && tmp->next->content != NULL)
	{
		new = expand_new(tmp->content);
		next = (*list)->next;
		(*list)->next = new;
		new->next = next;
		(*list) = new;
		tmp = tmp->next;
	}
	if (is_connect_next(tmp->content))
	{
		*line = tmp->content;
		new = expand_new(tmp->content);
		next = (*list)->next;
		(*list)->next = new;
		new->next = next;
		(*list) = new;
		tmp = tmp->next;
		return ((*list)->argv);
	}
	else
	{
		return (NULL);
	}
}
