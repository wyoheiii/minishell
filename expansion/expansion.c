#include "expansion.h"
#include "parser.h"

static bool	search_variable(char *str, size_t *index)
{
	size_t	length;
	bool	is_quote;

	length = ft_strlen(str);
	is_quote = false;
	while ((*index) < length)
	{
		if (is_quote && str[(*index)] == '\'')
			is_quote = false;
		else if (str[(*index)] == '\'')
			is_quote = true;
		else
		{
			if (str[(*index)] == '$')
				break ;
		}
		(*index) += 1;
	}
	if ((*index) == length)
		return (false);
	return (true);
}

size_t	get_name_size(const char *line, const size_t start)
{
	size_t	size;

	size = 0;
	if (line[(start)] == '?')
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
	size_t	length;
	size_t	size;
	size_t	index;

	length = ft_strlen(line);
	(*start) += 1;
	size = get_name_size(line, *start);
	variable_name = (char *)malloc(sizeof(char) * (size + 1));
	if (variable_name == NULL)
		return (NULL);
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

bool	expansion(t_parsed *parsed)
{
	t_parsed	*current;
	char		*variable_name;
	char		*tmp;
	size_t		count;
	size_t		index;

	count = 0;
	current = parsed;
	while (current != NULL)
	{
		while (parsed->command[count] != NULL)
		{
			index = 0;
			while (search_variable(parsed->command[count], &index))
			{
				variable_name = get_variable_name(parsed->command[count],
						&index);
				if (variable_name == NULL)
					return (false);
			}
			printf("%ld %s\n", count, variable_name);
			count += 1;
		}
		current = current->next;
	}
	return (true);
}
