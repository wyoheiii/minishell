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

//クォートか、変数か、その他か調べる
//クォートは取り除かれる
static bool	check_func(t_expand *list, size_t index)
{
	if (list->flag == NONE && list->argv[index] == '\'')
		list->flag = SINGLE;
	else if (list->flag == NONE && list->argv[index] == '\"')
		list->flag = DOUBLE;
	else if (list->flag == SINGLE && list->argv[index] == '\'')
		list->flag = NONE;
	else if (list->flag == DOUBLE && list->argv[index] == '\"')
		list->flag = NONE;
	else if (list->flag != SINGLE && list->argv[index] == '$'
		&& list->argv[index + 1] != '\0')
		return (false);
	else
		return (true);
	quote_remove(list->argv, index);
	return (false);
}

//リスト内の文字列を展開する
void	expand_argv(t_expand *list, t_envlist *envlist)
{
	char	*line;
	char	*tmp;
	char	*param;
	//t_list	*split;

	while (list != NULL)
	{
		line = ft_strdup("");
		while (list->argv[list->index] != '\0')
		{
			if (check_func(list, list->index) == true)
				list->index += 1;
			else if (list->flag != SINGLE && list->argv[list->index] == '$')
			{
				line = string_before_param(list, &line);
				param = param_func(list, envlist);
				/*
				if (list->flag == NONE)
				{
					split = word_splitting(param);
					if (split->content != NULL)
						tmp = func(&list, &line, split);
					else
						tmp = ft_strjoin(line, param);
				}
				else
				*/
				tmp = ft_strjoin(line, param);
				free(line);
				free(param);
				line = tmp;
			}
		}
		tmp = join_remaining_string(list, &line);
		if (tmp != NULL)
			line = tmp;
		free(list->argv);
		list->argv = line;
		list = list->next;
	}
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

void	expansion(t_parsed *parsed, t_envlist *env)
{
	t_expand	*argv_list;
	t_expand	*tmp;
	char		**new_command;
	size_t		size;

	while (parsed != NULL)
	{
		argv_list = convert_list(parsed->command);
		expand_argv(argv_list, env);
		tmp = argv_list;
		size = 0;
		while (tmp != NULL)
		{
			size += 1;
			tmp = tmp->next;
		}
		new_command = create_new_command(argv_list, size);
		free_expand(&argv_list);
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
