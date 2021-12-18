#include "lexer.h"

t_list	*lexer(const char *line)
{
	t_list	*token_list;
	t_list	*current;
	size_t	index;
	char	*token;

	index = 0;
	token_list = ft_lstnew("");
	while (line[index] != '\0' && line[index] != EOF)
	{
		token = get_token(&(line[index]), &index, ft_strlen(line));
		if (token == NULL)
			break ;
		current = ft_lstnew(token);
		if (current == NULL)
		{
			ft_lstclear(&token_list, free);
			return (NULL);
		}
		ft_lstadd_back(&token_list, current);
	}
	return (token_list);
}

/*
int main()
{
	t_list	*token_list;
	t_list	*tmp;
	char 	*str = "mkdir test| echo \"create test\">>log.txt | test\" aaa \' bbb \' hogehoge \" end";

	token_list = lexer(str);
	tmp = token_list->next;
	free(token_list);
	token_list = tmp;
	while (token_list != NULL)
	{
		printf("[%s]\n", (char *)token_list->content);
		tmp = token_list->next;
		free(token_list->content);
		free(token_list);
		token_list = tmp;
	}
	return (0);
}
*/