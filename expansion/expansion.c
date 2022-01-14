#include "expansion.h"

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
			str = get_expanded_line(current->command, &count);
			free(current->command[count]);
			current->command[count] = str;
			count += 1;
		}
		current = current->next;
	}
	return (true);
}
