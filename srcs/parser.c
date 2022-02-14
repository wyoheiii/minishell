/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkaneshi <tkaneshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 16:42:15 by tkaneshi          #+#    #+#             */
/*   Updated: 2022/02/14 16:42:18 by tkaneshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static char	**create_command(t_list **token_list, size_t size)
{
	char		**command;
	t_list		*tmp;
	size_t		index;

	command = (char **)malloc(sizeof(char *) * (size + 1));
	if (command == NULL)
	{
		ft_putendl_fd("malloc failure", 2);
		exit(EXIT_FAILURE);
	}
	index = 0;
	tmp = (*token_list);
	while (index < size)
	{
		if (is_delimiter(tmp->content) == false)
			command[index++] = tmp->content;
		else
			tmp = tmp->next;
		if (tmp == NULL)
			break ;
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
	{
		ft_putendl_fd("malloc failure", 2);
		exit(EXIT_FAILURE);
	}
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

static t_parsed	*get_parsed(t_list **token_list)
{
	size_t		size;
	char		**command;
	t_parsed	*parsed;
	t_redirect	*redirect;

	size = get_delimiter_count((*token_list));
	command = create_command(token_list, size);
	redirect = create_redirect(token_list);
	parsed = create_parsed(command, redirect);
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
		tmp = tmp->next;
	}
	return (parsed.next);
}
