#include "lexer.h"

t_list	*lexer(const char *line)
{
	t_list	token_list;
	t_list	*current;
	size_t	index;
	char	*token;

	index = 0;
	token_list.next = NULL;
	while (line[index] != '\0' && line[index] != EOF)
	{
		token = get_token(&(line[index]), &index, ft_strlen(line));
		if (token == NULL)
			break ;
		current = ft_lstnew(token);
		if (current == NULL)
		{
			ft_lstclear(&(token_list.next), free);
			return (NULL);
		}
		ft_lstadd_back(&(token_list.next), current);
	}
	return (token_list.next);
}

/* test code */
#include "parser.h"
#include "debug.h"
int main(int argc, char **argv)
{
	t_list		*token_list;
	t_parsed	*parsed;
//	char 	*str = "mkdir test| echo \"create test\">>log.txt | test\" aaa \' bbb \' hogehoge \" end";
//	char 	*str = "echo aaa > file > file | cat file | wc -l > file";
//	char 	*str = "echo aaa > file < file ccc bbb　> filea fffff";
//	char 	*str = "echo aaa > file < file bbb | cat < file | wc -l >> file << end";
	char 	*str = "a >";

	printf("[%s]\n", str);
	if (argc == 2)
		token_list = lexer(argv[1]);
	else if (argc == 1)
		token_list = lexer(str);
	else
	{
		printf("argv ga takusan aru\n");
		return (0);
	}
	if (token_list == NULL)
	{
		printf("token_list NULL\n");
		return (EXIT_FAILURE);
	}
	parsed = parser(&token_list);
	if (parsed == NULL)
	{
		print_token_list(token_list);
		printf("parsed NULL\n");
	}
	else
		print_parsed(parsed);
	free_parsed(&parsed);
	return (0);
}
