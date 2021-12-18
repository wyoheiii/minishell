#include "debug.h"

void	print_token_list(t_list *token_list)
{
	t_list	*tmp;
	size_t	count;

	tmp = token_list;
	count = 1;
	printf("*****token_list*****\n");
	while (tmp != NULL)
	{
		printf("%ld:[%s]\n", count, (char *)(tmp->content));
		count += 1;
		tmp = tmp->next;
	}
	printf("*******************\n");
}

static void	print_state(int state)
{
	if (state == NONE)
		printf("(NONE)");
	else if (state == PIPE)
		printf("(PIPE)");
	else if (state == REDIRECT_INPUT)
		printf("(REDIRECT_INPUT)");
	else if (state == REDIRECT_OUTPUT)
		printf("(REDIRECT_OUTPUT)");
	else if (state == REDIRECT_APPEND)
		printf("(REDIRECT_APPEND)");
	else if (state == HERE_DOCUMENT)
		printf("(HERE_DOCUMENT)");
	else
		printf("(ERROR!!!!!!!!!!!!!!!)");
}

void	print_parsed(t_parsed *parsed)
{
	t_parsed	*tmp;
	size_t		count;
	size_t		index;
	char		*state;

	tmp = parsed;
	count = 1;
	printf("*******parsed*******\n");
	while (tmp != NULL)
	{
		printf("%ld", count++);
		print_state(tmp->state);
		index = 0;
		while (tmp->command[index] != NULL)
			printf("[%s]", (char *)(tmp->command[index++]));
		printf("\n");
		tmp = tmp->next;
	}
	printf("*******************\n");
}
