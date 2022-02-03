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

	if (start != index)
	{
		remaining = my_substr(str, start, index - start);
		*line = my_strjoin(line, &remaining);
	}
}

void	split_to_command(char **command, size_t *count, t_list *list)
{

}

static char	*expand_line(char **command, size_t *count,
	size_t *index, size_t *start)
{
	int		flag;
	char	*line;
	char	*param;

	flag = NONE;
	line = (char *)my_calloc(1, sizeof(char));
	while (command[*count][*index] != '\0')
	{
		if (check_func(command[*count], *index, &flag))
			*index += 1;
		if (flag != SINGLE && command[*count][*index] == '$')
		{
			if (command[*count][*index] == '$' && command[*count][*index + 1] == '\0')
			{
				(*index) += 1;
				break ;
			}
			string_before_param(command[*count], &line, index, start);
			param = param_func(command[*count], line, index, start);
			if (param != NULL)
			{
				if (flag == DOUBLE)
				{
					t_list	*splited;
					splited = word_splitting(param);

				}
				else
				{
					line = my_strjoin(&line, &param);
				}
			}
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
		line = my_strdup(command[*count]);
	}
	return (line);
}
