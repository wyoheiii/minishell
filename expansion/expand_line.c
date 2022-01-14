#include "expand_line.h"

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

static void	join_remaining_string(char **line, char *str,
	size_t index, size_t start)
{
	char	*remaining;
	char	*joined;

	if (start != index)
	{
		remaining = ft_substr(str, start, index - start);
		if (remaining == NULL)
		{
			ft_putendl_fd("malloc failure", 2);
			exit(EXIT_FAILURE);
		}
		joined = ft_strjoin(*line, remaining);
		free(remaining);
		if (joined == NULL)
		{
			ft_putendl_fd("malloc failure", 2);
			exit(EXIT_FAILURE);
		}
		free(*line);
		*line = joined;
	}
}

static char	*expand_line(char **command, size_t *count,
	size_t *index, size_t *start)
{
	int		flag;
	char	*line;

	flag = NONE;
	line = (char *)ft_calloc(1, sizeof(char));
	if (line == NULL)
	{
		ft_putendl_fd("malloc failure\n", 2);
		exit(EXIT_FAILURE);
	}
	while (command[*count][*index] != '\0')
	{
		if (check_func(command[*count], *index, &flag))
			*index += 1;
		if (flag != SINGLE && command[*count][*index] == '$')
		{
			line = param_func(command[*count], line, index, start);
			if (flag == DOUBLE)
				word_split(line, &command, count);
		}
	}
	join_remaining_string(&line, command[*count], *index, *start);
	return (line);
}

char	*get_expanded_line(char **command, size_t *count)
{
	size_t	index;
	size_t	start;
	char	*line;

	index = 0;
	start = 0;
	line = expand_line(command, count, &index, &start);
	if (command[*count][0] != '$' && line[0] == '\0')
	{
		free(line);
		line = ft_strdup(command[*count]);
		if (line == NULL)
		{
			ft_putendl_fd("malloc failure\n", 2);
			exit(EXIT_FAILURE);
		}
	}
	return (line);
}
