#include "expand_argv.h"

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

static bool	set_quote_flag(t_expand *list, size_t index)
{
	if (list->flag == NONE && list->argv[index] == '\'')
		list->flag = SINGLE;
	else if (list->flag == NONE && list->argv[index] == '\"')
		list->flag = DOUBLE;
	else if (list->flag == SINGLE && list->argv[index] == '\'')
		list->flag = NONE;
	else if (list->flag == DOUBLE && list->argv[index] == '\"')
		list->flag = NONE;
	else
		return (false);
	return (true);
}

static size_t	search_expand_char(t_expand *list, size_t index)
{
	while (list->argv[index] != '\0')
	{
		if (set_quote_flag(list, index))
			break ;
		if (list->flag != SINGLE && list->argv[index] == '$')
			break ;
		index += 1;
	}
	return (index);
}

static void	add_remaining(t_expand *new, t_expand *list)
{
	t_expand	*current;
	char		*str;
	size_t		length;

	length = ft_strlen(list->argv);
	if (list->checked < length)
	{
		str = my_substr(list->argv, list->checked, list->index);
		current = new;
		while (current->next != NULL)
			current = current->next;
		if (current->is_join)
			current->argv = my_strjoin(&(current->argv), &str);
		else
			expand_add_back(&new, expand_new(str));
	}
}

t_expand	*expand_argv(t_expand *list, t_envlist *envlist)
{
	t_expand	new_list;
	t_expand	*tmp;
	bool		flag;

	new_list.next = NULL;
	while (list != NULL)
	{
		flag = true;
		tmp = expand_new(my_strdup(""));
		tmp->is_join = true;
		while (list->argv != NULL && list->argv[list->index] != '\0')
		{
			list->index = search_expand_char(list, list->index);
			if (is_remove(list))
				quote_remove(list->argv, list->index);
			else if (is_expand(list))
				flag = add_expanded_param(tmp, list, envlist);
		}
		if (list->argv != NULL && (flag || tmp->argv[0] != '\0'))
		{
			add_remaining(tmp, list);
			expand_add_back(&(new_list.next), tmp);
		}
		list = list->next;
	}
	return (new_list.next);
}
