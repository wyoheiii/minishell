#include "expand_param.h"

static bool	expand_variable(char **line, char *variable_name)
{
	char	*tmp;
	char	*tmp2;

	tmp = getenv(variable_name);
	if (tmp != NULL)
	{
		tmp2 = ft_strjoin(*line, tmp);
		if (tmp2 == NULL)
		{
			//error
		}
		free(*line);
		*line = tmp2;
	}
	return (true);
}

static bool	expand_exit_status(char *str, char **line)
{
	char	*tmp;

	tmp = ft_strjoin(*line, "0");
	if (str == NULL)
	{
		//error
	}
	free(*line);
	*line = tmp;
	return (true);
}

static bool	string_before_param(char *str, char **line,
		size_t *index, size_t *start)
{
	char	*tmp;
	char	*tmp2;

	if (*index != *start)
	{
		tmp = ft_substr(str, *start, (*index - *start));
		if (tmp == NULL)
		{
			//error
			return (false);
		}
		tmp2 = ft_strjoin(*line, tmp);
		free(*line);
		free(tmp);
		*line = tmp2;
	}
	return (true);
}

char	*param_func(char *str, char *line, size_t *index, size_t *start)
{
	char	*variable_name;
	bool	is_ok;

	is_ok = true;
	if (!string_before_param(str, &line, index, start))
	{
		// substr error
	}
	variable_name = get_variable_name(str, index);
	if (variable_name == NULL)
		return (false);
	if (variable_name[0] == '?')
		is_ok = expand_exit_status(str, &line);
	else
		is_ok = expand_variable(&line, variable_name);
	if (is_ok == false)
	{
		// strjoin error
	}
	(*start) = (*index);
	free(variable_name);
	return (line);
}
