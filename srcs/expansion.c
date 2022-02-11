#include "expansion.h"

//取り除いた後、使用しないメモリが生まれるのでstrはコピーし、freeすること
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

// フラグを更新したらtrue
bool	set_quote_flag(t_expand *list, size_t index)
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

bool	is_remove(t_expand *list)
{
	if (list->flag == NONE
		&& (list->argv[list->index] == '\''
			|| list->argv[list->index] == '\"'))
		return (true);
	else if (list->flag == SINGLE && list->argv[list->index] == '\'')
		return (true);
	else if (list->flag == DOUBLE && list->argv[list->index] == '\"')
		return (true);
	return (false);
}

bool	is_expand(t_expand *list)
{
	if (list->flag != SINGLE && (list->argv[list->index] == '$'
			&& list->argv[list->index] != '\0'))
		return (true);
	return (false);
}

void	expand_join_last(t_expand *new, char *str)
{
	while (new->next != NULL)
		new = new->next;
	if (new->argv == NULL)
		new->argv = my_strdup(str);
	else
		new->argv = my_strjoin(&(new->argv), &str);
}

void	expand_joinflag_on(t_expand *new)
{
	while (new->next != NULL)
		new = new->next;
	new->is_join = true;
}

void	expand_add_split(t_expand *new, char *param)
{
	t_list	*split;
	t_list	*tmp;

	split = word_splitting(param);
	if (split == NULL)
		split = ft_lstnew(param);
	if (!ft_isspace(param[0]))
	{
		tmp = split;
		expand_join_last(new, (char *)tmp->content);
		split = split->next;
		free(tmp);
	}
	while (split != NULL)
	{
		tmp = split;
		expand_add_back(&new, expand_new(tmp->content));
		split = split->next;
		free(tmp);
	}
}

bool	add_expanded_param(t_expand *new, t_expand *list, t_envlist *envlist)
{
	char	*str;
	char	*param;

	if (list->index != list->checked)
	{
		str = my_substr(list->argv, list->checked,
				(list->index - list->checked));
		expand_join_last(new, str);
	}
	param = param_func(list, envlist);
	list->checked = list->index;
	if (param == NULL && list->flag == DOUBLE)
		return (true);
	else if (param == NULL)
		return (false);
	if (list->flag == NONE)
		expand_add_split(new, param);
	else
		expand_join_last(new, param);
	if (!ft_isspace(param[ft_strlen(param) - 1]))
		expand_joinflag_on(new);
	return (true);
}

void	add_remaining(t_expand *new, t_expand *list)
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

//リスト内の文字列を展開する
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
		while (list->argv[list->index] != '\0')
		{
			list->index = search_expand_char(list, list->index);
			if (is_remove(list))
				quote_remove(list->argv, list->index);
			else if (is_expand(list))
				flag = add_expanded_param(tmp, list, envlist);
		}
		if (flag || tmp->argv[0] != '\0')
		{
			add_remaining(tmp, list);
			expand_add_back(&(new_list.next), tmp);
		}
		list = list->next;
	}
	return (new_list.next);
}

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

size_t	expand_lst_size(t_expand *argv_list)
{
	t_expand	*tmp;
	size_t		size;

	tmp = argv_list;
	size = 0;
	while (tmp != NULL)
	{
		size += 1;
		tmp = tmp->next;
	}
	return (size);
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

/*
// main for debug
int main(int argc, char **argv, char **envp)
{
	t_expand  *list;
	t_expand  *tmp;
	t_envlist *envlist;
	char    **test;

	env_init(envp, &envlist);
	test = malloc(sizeof(char *) * 5);

	test[0] = ft_strdup("echo");
	test[1] = ft_strdup("hell\"o\"");
	test[2] = ft_strdup("test$HOME$");
	test[3] = ft_strdup("hogehoge");
	test[4] = NULL;

	list = convert_list(test);
	tmp = list;

	do
	{
		printf("%s\n", tmp->argv);
		tmp = tmp->next;
	} while (tmp != NULL);

	expand_argv(list, envlist);
	tmp = list;


//	free(test);


	return (0);
}
*/
