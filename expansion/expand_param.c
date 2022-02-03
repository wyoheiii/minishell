#include "expand_param.h"

void	string_before_param(char *str, char **line,
		size_t *index, size_t *start)
{
	char	*before_param;

	if (*index != *start)
	{
		before_param = my_substr(str, *start, (*index - *start));
		*line = my_strjoin(line, &before_param);
	}
}

static char	*expand_variable(char *variable_name)
{
	char	*value;
	char	*dup;

	dup = NULL;
	value = getenv(variable_name);
	if (value != NULL)
		dup = my_strdup(value);
	return (dup);
}

static char	*expand_exit_status(void)
{
	char	*status;

	status = my_strdup("0");
	return (status);
}

char	*param_func(char *str, char *line, size_t *index, size_t *start)
{
	char	*variable_name;
	char	*param;

	variable_name = get_variable_name(str, index);
	if (variable_name[0] == '?')
		param = expand_exit_status();
	else
		param = expand_variable(variable_name);
	free(variable_name);
	(*start) = (*index);
	return (param);
}
