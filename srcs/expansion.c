#include "expansion.h"

char	**create_new_command(t_expand *argv_list, size_t size)
{
	char		**new_command;
	t_expand	*tmp;
	size_t		index;

	new_command = (char **)malloc(sizeof(char *) * (size + 1));
	index = 0;
	tmp = argv_list;
	while (index < size)
	{
		new_command[index] = tmp->argv;
		index += 1;
		tmp = tmp->next;
	}
	new_command[index] = NULL;
	return (new_command);
}

void	expansion(t_parsed *parsed, t_envlist *env)
{
	t_expand	*argv_list;
	t_expand	*expand_argv_list;
	char		**new_command;
	size_t		size;

	while (parsed != NULL)
	{
		argv_list = convert_list(parsed->command);
		expand_argv_list = expand_argv(argv_list, env);
		free_expand(&argv_list);
		size = expand_lst_size(expand_argv_list);
		new_command = create_new_command(expand_argv_list, size);
		free_expand(&expand_argv_list);
		free(parsed->command);
		parsed->command = new_command;
		parsed = parsed->next;
	}
}
