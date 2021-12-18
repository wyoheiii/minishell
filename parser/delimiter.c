#include "delimiter.h"

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

int	get_state(char *str)
{
	int	state;

	state = NONE;
	if (str[0] == '|')
		state = PIPE;
	else if (str[0] == '<')
	{
		if (fr_strlen(str) == 2 && str[1] == '<')
			state = HERE_DOCUMENT;
		else
			state = REDIRECT_INPUT;
	}
	else if (str[0] == '>')
	{
		if (fr_strlen(str) == 2 && str[1] == '>')
			state = REDIRECT_APPEND;
		else
			state = REDIRECT_OUTPUT;
	}
}
