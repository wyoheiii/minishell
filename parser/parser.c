#include "libft.h"

#include <stdbool.h>
#include <stdlib.h>

typedef struct s_parsed
{
	char			**command;
	struct s_parsed	*next;
}	t_parsed;

t_parsed	*create_parsed(char **command)
{
	t_parsed	*parsed;

	parsed = (t_parsed *)malloc(sizeof(t_parsed));
	if (parsed == NULL)
		return (NULL);
	parsed->command = command;
	parsed->next = NULL;
	return (parsed);
}

bool	is_delimiter(char *str)
{
	if (str[0] == '|' || str[0] == '<' || str[0] == '>')
		return (true);
	return (false);
}

size_t	get_delimiter_count(t_list *token_list)
{
	size_t	count;
	t_list	*tmp;

	count = 0;
	tmp = token_list;
	while (tmp != NULL)
	{
		if (is_delimiter(tmp->content))
			break ;
		count += 1;
		tmp = tmp->next;
	}
	return (count);
}

char	**create_command(t_list **token_list, size_t size)
{
	char		**command;
	t_list		*tmp;
	size_t		index;

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

t_parsed	*parser(t_list *token_list)
{
	t_parsed	*parsed;
	t_list		*tmp;
	t_parsed	*tmp2;
	size_t		size;
	char		**command;

	tmp = token_list->next;
	free (token_list);
	token_list = tmp;
	parsed = (t_parsed *)malloc(sizeof(t_parsed));
	tmp2 = parsed;
	while (token_list != NULL)
	{
		size = get_delimiter_count(token_list);
		command = (char **)malloc(sizeof(char *) * (size + 1));
		if (command == NULL)
		{
			//error
		}
		command = create_command(&token_list, size);
		tmp2->next = create_parsed(command);
		if (token_list != NULL && is_delimiter(token_list->content))
		{
			tmp = token_list->next;
			free(token_list);
			token_list = tmp;
		}
		tmp2 = tmp2->next;
	}
	tmp2 = parsed->next;
	free(parsed);
	parsed = tmp2;
	return (parsed);
}
