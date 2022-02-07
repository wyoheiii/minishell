#include "expansion.h"
#include "minishell_c.h"

/*
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
*/

#include "libft.h"
#include "parser.h"
#include "stdio.h"

# define NONE	0
# define SINGLE 1
# define DOUBLE 2
# define DELIMITER " \t\n"

typedef struct s_expand
{
	char			*argv;
	int				flag;
	size_t			index;
	size_t			checked;
	struct s_expand	*next;
} t_expand;

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
	t_expand *current;

	current = *head;
	while (current->next != NULL)
		current = current->next;
	current->next = new;
}

// 文字列の配列をリストにする
t_expand *convert_list(char **command)
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


char	*string_before_param(t_expand *list, char **line)
{
	char	*before_param;
	char	*new_line;

	if (list->index != list->checked)
	{
		before_param = ft_substr(list->argv, list->checked,
			(list->index - list->checked));
		if (before_param == NULL)
		{
			ft_putendl_fd("malloc failure", 2);
			exit(EXIT_FAILURE);
		}
		new_line = ft_strjoin(*line, before_param);
		free(*line); 
		free(before_param);
		if (new_line == NULL)
		{
			ft_putendl_fd("malloc failure", 2);
			exit(EXIT_FAILURE);
		}
		return (new_line);
	}
	return (*line);
}

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

char	*param_func(t_expand *list, t_envlist *envlist)
{
	char	*variable_name;
	char	*param;

	variable_name = get_variable_name(list->argv, &list->index);
	param = search_env_key_(variable_name, envlist);
	free(variable_name);
	list->checked = list->index;
	return (param);
}

char	*join_remaining_string(t_expand *list, char **line)
{
	char	*remaining;
	char	*new_command;

	if (list->checked != list->index)
	{
		remaining = ft_substr(
			list->argv, list->checked, list->index - list->checked);
		if (remaining == NULL)
		{
			ft_putendl_fd("malloc failure", 2);
			exit(EXIT_FAILURE);
		}
		new_command = ft_strjoin(*line, remaining);
		free(*line);
		free(remaining);
		if (new_command == NULL)
		{
			ft_putendl_fd("malloc failure", 2);
			exit(EXIT_FAILURE);
		}
		return (new_command);
	}
	return (NULL);
}

t_list	*my_lstnew(void *content)
{
	t_list	*new_list;

	new_list = ft_lstnew(content);
	if (new_list == NULL)
	{
		ft_putendl_fd("malloc failure", 2);
		exit(EXIT_FAILURE);
	}
	return (new_list);
}

void	lstnew_add_back(t_list **lst, void *content)
{
	t_list	*new_list;

	new_list = my_lstnew(content);
	ft_lstadd_back(lst, new_list);
}

t_list	*word_splitting(char *str)
{
	t_list	*splitted;
	size_t	index;
	size_t	length;
	char	*tmp;

	index = 0;
	length = 0;
	splitted = NULL;
	while (str[index] != '\0')
	{
		if (ft_strrchr(DELIMITER, str[index]))
		{
			if (length > 0)
			{
				tmp = ft_substr(str, index - length, length);
				if (tmp == NULL)
				{
					ft_putendl_fd("malloc failure", 2);
					exit(EXIT_FAILURE);
				}
				lstnew_add_back(&splitted, tmp);
			}
			length = 0;
		}
		else
			length += 1;
		index += 1;
	}
	return (splitted);
}

//リスト内の文字列を展開する
void	expand_argv(t_expand *list, t_envlist *envlist)
{
	char	*line;
	char	*tmp;
	char	*param;
//	t_list	*split;

	while (list != NULL)
	{
		line = ft_strdup("");
		while (list->argv[list->index] != '\0')
		{
			if (check_func(list, list->index) == true)
				list->index += 1;
			else if (list->argv[list->index] == '$')
			{
				line = string_before_param(list, &line);
				param = param_func(list, envlist);		//パラメータの値を取得
				tmp = ft_strjoin(line, param);
				//split = word_splitting(param);	//単語分割したリスト
				//func(&list, &line, split);
				//free(param);
				free(line);
				free(param);
				line = tmp;
			}
		}
		tmp = join_remaining_string(list, &line);
		if (tmp != NULL && tmp[0] != '\0')
			line = tmp;
		printf("env:%s\n", line);
		//free(list->argv);
		list->argv = line;
		list = list->next;
	}
}

void    expansion(t_parsed *parsed, t_envlist *env)
{
	t_expand	*argv_list;
	t_expand	*tmp;
	char		**new_command;
	size_t		size;

	argv_list = convert_list(parsed->command);
	expand_argv(argv_list, env);
	tmp = argv_list;
	size = 0;
	while (tmp->next != NULL)
	{
		size += 1;
		tmp = tmp->next;
	}
	new_command = (char **)malloc(sizeof(char *) * size);
	size = 0;
	tmp = argv_list;
	while (tmp->next != NULL)
	{
		new_command[size] = tmp->argv;
		tmp = tmp->next;
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

	do
	{
		printf("%s\n", list->argv);
		tmp = list->next;
//		free(list->argv);
//		free(list);
		list = tmp;
	} while (list != NULL);

//	free(test);


	return (0);
}
*/
