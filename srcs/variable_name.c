#include "variable_name.h"

static size_t	get_name_size(const char *line, const size_t start)
{
	size_t	size;

	size = 0;
	if (line[(start)] == '?')
		size += 1;
	else if (ft_isdigit(line[(start)]))
		size += 1;
	else
		while (ft_isalnum(line[(start + size)])
			|| line[(start + size)] == '_')
			size += 1;
	return (size);
}

char	*get_variable_name(char *line, size_t *start)
{
	char	*variable_name;
	size_t	size;
	size_t	index;

	(*start) += 1;
	size = get_name_size(line, *start);
	variable_name = (char *)malloc(sizeof(char) * (size + 1));
	if (variable_name == NULL)
	{
		ft_putendl_fd("malloc failure", 2);
		exit(EXIT_FAILURE);
	}
	index = 0;
	while (index < size)
	{
		variable_name[index] = line[(*start) + index];
		index += 1;
	}
	(*start) += size;
	variable_name[index] = '\0';
	return (variable_name);
}
