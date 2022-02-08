#include "expand_struct.h"

t_expand	*expand_new(char *argv)
{
	t_expand	*new;

	new = (t_expand *)malloc(sizeof(t_expand));
	if (new == NULL)
	{
		ft_putendl_fd("malloc failure", 2);
		exit(EXIT_FAILURE);
	}
	new->argv = argv;
	new->flag = NONE;
	new->index = 0;
	new->checked = 0;
	new->next = NULL;
	return (new);
}

void	expand_add_back(t_expand **head, t_expand *new)
{
	t_expand	*current;

	current = *head;
	while (current->next != NULL)
		current = current->next;
	current->next = new;
}

// 文字列の配列をリストにする
t_expand	*convert_list(char **command)
{
	t_expand	*new;
	t_expand	*tmp;
	size_t		size;
	size_t		index;

	size = 0;
	while (command[size] != NULL)
		size += 1;
	index = 0;
	new = expand_new(command[index++]);
	if (new == NULL)
	{
		ft_putendl_fd("malloc failure", 2);
		exit(EXIT_FAILURE);
	}
	while (index < size)
	{
		tmp = expand_new(command[index++]);
		expand_add_back(&new, tmp);
	}
	return (new);
}
