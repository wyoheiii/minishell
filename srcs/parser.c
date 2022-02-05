#include "parser.h"
#include <stdio.h>
static char	**create_command(t_list **token_list, size_t size)
{
	char		**command;
	t_list		*tmp;
	size_t		index;

	command = (char **)malloc(sizeof(char *) * (size + 1));
	if (command == NULL)
		return (NULL);
	index = 0;
	tmp = (*token_list);
	while (index < size)
	{
		if (is_delimiter(tmp->content) == false)
		{
			command[index] = tmp->content;
			index += 1;
		}
		else
			tmp = tmp->next;
		tmp = tmp->next;
	}
	command[size] = NULL;
	return (command);
}

static t_parsed	*create_parsed(char **command, t_redirect *redirect)
{
	t_parsed	*parsed;

	parsed = (t_parsed *)malloc(sizeof(t_parsed));
	if (parsed == NULL)
		return (NULL);
	parsed->command = command;
	parsed->redirect = redirect;
	parsed->state = NONE;
	parsed->next = NULL;
	return (parsed);
}

void	free_parsed(t_parsed **parsed)
{
	t_parsed	*tmp;
	t_redirect	*redirect;
	size_t		index;

	while ((*parsed) != NULL)
	{
		tmp = (*parsed)->next;
		index = 0;
		while ((*parsed)->command[index] != NULL)
			free((*parsed)->command[index++]);
		while ((*parsed)->redirect != NULL)
		{
			redirect = (*parsed)->redirect->next;
			free((*parsed)->redirect->filename);
			free((*parsed)->redirect);
			(*parsed)->redirect = redirect;
		}
		free((*parsed)->command);
		free(*parsed);
		(*parsed) = tmp;
	}
}

t_redirect	*new_redirect(char	*filename, char *meta)
{
	t_redirect	*redirect;

	redirect = (t_redirect *)malloc(sizeof(t_redirect));
	if (redirect == NULL)
		return (NULL);
	redirect->filename = filename;
	redirect->state = get_state(meta);
	redirect->next = NULL;
	return (redirect);
}

void	redirect_add_back(t_redirect **head, t_redirect *new)
{
	t_redirect	*tmp;

	if (*head == NULL)
	{
		*head = new;
		return ;
	}
	tmp = *head;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
}

t_redirect	*create_redirect(t_list **token_list)
{
	t_redirect	*redirect;
	t_redirect	*new;
	t_list		*tmp;

	redirect = NULL;
	while ((*token_list) != NULL && is_pipe((*token_list)->content) == NONE)
	{
		if (is_redirect((*token_list)->content))
		{
			tmp = (*token_list)->next;
			new = new_redirect(tmp->content, (*token_list)->content);
			if (new == NULL)
				return (NULL);
			redirect_add_back(&redirect, new);
			free((*token_list)->content);
			//free(((*token_list)->next->content));
			free(*token_list);
			*token_list = tmp;
		}
		tmp = (*token_list)->next;
		free(*token_list);
		*token_list = tmp;
	}
	new = new_redirect(NULL, NULL);
	redirect_add_back(&redirect, new);	
	return (redirect);
}

/*
t_parsedはpipeでわける
echo aaa > file1 bbb > file2
のようにリダイレクト指定の後に引数がある可能性がある

commandはtokenlistからpipeが見つかるまで調べていく
commandのサイズは >  < が見つかると-2していく

|, NULL ->終了
>, < 	->次に来る文字列はファイル名でありコマンド、引数ではない
文字列	->コマンド

*/

static t_parsed	*get_parsed(t_list **token_list)
{
	size_t		size;
	char		**command;
	t_parsed	*parsed;
	t_redirect	*redirect;

	size = get_delimiter_count((*token_list));
	command = create_command(token_list, size);
	if (command == NULL || command[0] == NULL)
		return (NULL);
	redirect = create_redirect(token_list);
	parsed = create_parsed(command, redirect);
	if (parsed == NULL)
	{
		free(command);
		return (NULL);
	}
	if ((*token_list) != NULL && is_delimiter((*token_list)->content))
	{
		parsed->state = get_state((*token_list)->content);
		lstdel_front(token_list);
	}
	return (parsed);
}

t_parsed	*parser(t_list **token_list)
{
	t_parsed	parsed;
	t_parsed	*tmp;

	parsed.next = NULL;
	tmp = &parsed;
	while ((*token_list) != NULL)
	{
		tmp->next = get_parsed(token_list);
		if (tmp->next == NULL)
		{
			ft_lstclear(token_list, free);
			free_parsed(&(parsed.next));
			return (NULL);
		}
		tmp = tmp->next;
	}
	return (parsed.next);
}
