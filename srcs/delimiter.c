#include "delimiter.h"

int	is_pipe(char *str)
{
	if (str == NULL)
		return (NONE);
	if (str[0] == '|')
		return (PIPE);
	return (NONE);
}

int	is_redirect(char *str)
{
	if (str == NULL)
		return (NONE);
	if (str[0] == '<')
		return (REDIRECT_INPUT);
	else if (str[0] == '>')
		return (REDIRECT_OUTPUT);
	return (NONE);
}

bool	is_delimiter(char *str)
{
	if (is_pipe(str) || is_redirect(str))
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
		if (is_pipe(tmp->content))
			break ;
		else if (is_redirect(tmp->content))
		{
			if (tmp->next != NULL && tmp->content != NULL)
			{
				tmp = tmp->next->next;
				continue ;
			}
		}
		count += 1;
		tmp = tmp->next;
	}
	return (count);
}

int	get_state(char *str)
{
	int	state;

	state = NONE;
	if (str == NULL)
		return (state);
	if (str[0] == '|')
		state = PIPE;
	else if (str[0] == '<')
	{
		if (ft_strlen(str) == 2 && str[1] == '<')
			state = HERE_DOCUMENT;
		else
			state = REDIRECT_INPUT;
	}
	else if (str[0] == '>')
	{
		if (ft_strlen(str) == 2 && str[1] == '>')
			state = REDIRECT_APPEND;
		else
			state = REDIRECT_OUTPUT;
	}
	return (state);
}
