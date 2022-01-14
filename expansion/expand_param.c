#include "expand_param.h"

static void	expand_variable(char **line, char *variable_name)
{
	char	*value;
	char	*joined;

	value = getenv(variable_name);
	if (value != NULL)
	{
		joined = ft_strjoin(*line, value);
		if (joined == NULL)
		{
			ft_putendl_fd("malloc failure", 2);
			exit(EXIT_FAILURE);
		}
		free(*line);
		*line = joined;
	}
}

static void	expand_exit_status(char *str, char **line)
{
	char	*tmp;

	tmp = ft_strjoin(*line, "0");
	if (str == NULL)
	{
		ft_putendl_fd("malloc failure", 2);
		exit(EXIT_FAILURE);
	}
	free(*line);
	*line = tmp;
}

static void	string_before_param(char *str, char **line,
		size_t *index, size_t *start)
{
	char	*before_param;
	char	*joined;

	if (*index != *start)
	{
		before_param = ft_substr(str, *start, (*index - *start));
		if (before_param == NULL)
		{
			ft_putendl_fd("malloc failure", 2);
			exit(EXIT_FAILURE);
		}
		joined = ft_strjoin(*line, before_param);
		free(before_param);
		if (joined == NULL)
		{
			ft_putendl_fd("malloc failure", 2);
			exit(EXIT_FAILURE);
		}
		free(*line);
		*line = joined;
	}
}

char	*param_func(char *str, char *line, size_t *index, size_t *start)
{
	char	*variable_name;

	if (str[*index + 1] == '\0')
	{
		(*index) += 1;
		return (line);
	}
	string_before_param(str, &line, index, start);
	variable_name = get_variable_name(str, index);
	if (variable_name[0] == '?')
		expand_exit_status(str, &line);
	else
		expand_variable(&line, variable_name);
	free(variable_name);
	(*start) = (*index);
	return (line);
}
