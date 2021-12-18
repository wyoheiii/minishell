#include "parser.h"

static char	**create_command(t_list **token_list, size_t size)
{
	char		**command;
	t_list		*tmp;
	size_t		index;

	command = (char **)malloc(sizeof(char *) * (size + 1));
	if (command == NULL)
		return (NULL);
	index = 0;
	while (index < size)
	{
		command[index] = (*token_list)->content;
		tmp = (*token_list)->next;
		free(*token_list);
		(*token_list) = tmp;
		index += 1;
	}
	command[size] = NULL;
	return (command);
}

static t_parsed	*create_parsed(char **command)
{
	t_parsed	*parsed;

	parsed = (t_parsed *)malloc(sizeof(t_parsed));
	if (parsed == NULL)
		return (NULL);
	parsed->command = command;
	parsed->state = NONE;
	parsed->next = NULL;
	return (parsed);
}

static t_parsed	*get_parsed(t_list **token_list)
{
	size_t		size;
	char		**command;
	t_parsed	*tmp;

	size = get_delimiter_count((*token_list));
	command = create_command(token_list, size);
	if (command == NULL)
		return (NULL);
	tmp->next = create_parsed(command);
	if (tmp->next == NULL)
	{
		free(command);
		return (NULL);
	}
	if ((*token_list) != NULL && is_delimiter((*token_list)->content))
	{
		tmp->next->state = get_state((*token_list)->content);
		lstdel_front(token_list);
	}
	return (true);
}

void	free_parsed(t_parsed **parsed)
{
	t_parsed	*tmp;

	while ((*parsed) != NULL)
	{
		tmp = (*parsed)->next;
		free(*parsed);
		(*parsed) = tmp;
	}
}

t_parsed	*parser(t_list **token_list)
{
	t_parsed	parsed;
	t_parsed	*tmp;

	lstdel_front(token_list);
	parsed.next = NULL;
	tmp = &parsed;
	while ((*token_list) != NULL)
	{
		tmp->next = get_parsed(token_list);
		if (tmp->next == NULL)
		{
			ft_lstclear(token_list, free);
			free_parsed(&parsed);
			return (NULL);
		}
		tmp = tmp->next;
	}
	ft_lstclear(token_list, free);
	return (parsed.next);
}