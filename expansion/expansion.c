#include "expansion.h"

static void	quote_remove(char *str, size_t start)
{
	size_t	index;

	index = start + 1;
	if (str[index] == '\0')
		str[start] = '\0';
	else
	{
		while (str[index] != '\0')
			str[start++] = str[index++];
		str[start] = '\0';
	}
}

static bool	check_func(char *str, size_t index, int *flag)
{
	if ((*flag) == NONE && str[index] == '\'')
		(*flag) = SINGLE;
	else if ((*flag) == NONE && str[index] == '\"')
		(*flag) = DOUBLE;
	else if ((*flag) == SINGLE && str[index] == '\'')
		(*flag) = NONE;
	else if ((*flag) == DOUBLE && str[index] == '\"')
		(*flag) = NONE;
	else if ((*flag) != SINGLE && str[index] == '$')
		return (false);
	else
		return (true);
	quote_remove(str, index);
	return (false);
}

static char	*get_expanded_line(char *str)
{
	size_t	index;
	size_t	start;
	char	*tmp;
	char	*tmp2;
	char	*line;
	int		flag;

	index = 0;
	start = 0;
	flag = NONE;

	line = ft_calloc(1, sizeof(char));
	if (line == NULL)
	{
		// error
	}
	while (str[index] != '\0')
	{
		if (check_func(str, index, &flag))
			index += 1;
		if (flag != SINGLE && str[index] == '$')
		{
			line = param_func(str, line, &index, &start);
		}
	}
	if (start != index)
	{
		tmp = ft_substr(str, start, index - start);

		tmp2 = ft_strjoin(line, tmp);

		free(line);
		free(tmp);
		line = tmp2;

	}
	if (str[0] != '$' && line[0] == '\0')
	{
		line = ft_strdup(str);
		if (str == NULL)
		{
			// error
		}
	}
	return (line);
}

bool	expansion(t_parsed *parsed)
{
	char		*str;
	size_t		count;
	t_parsed	*current;

	current = parsed;
	while (current != NULL)
	{
		count = 0;
		while (current->command[count] != NULL)
		{
			str = get_expanded_line(current->command[count]);
			if (str == NULL)
			{
				// error
			}
			free(current->command[count]);
			current->command[count] = str;
			count += 1;
		}
		current = current->next;
	}
	return (true);
}
