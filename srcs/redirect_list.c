/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyohei <wyohei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 16:43:45 by tkaneshi          #+#    #+#             */
/*   Updated: 2022/02/23 20:10:17 by wyohei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirect_list.h"

static t_redirect	*new_redirect(char	*filename, char *meta)
{
	t_redirect	*redirect;

	redirect = (t_redirect *)malloc(sizeof(t_redirect));
	if (redirect == NULL)
	{
		ft_putendl_fd("malloc failure", 2);
		exit(EXIT_FAILURE);
	}
	redirect->tmpfile = NULL;
	redirect->fd = -1;
	redirect->filename = filename;
	redirect->state = get_state(meta);
	redirect->is_error = NONE;
	redirect->quote = NONE;
	redirect->next = NULL;
	return (redirect);
}

static void	redirect_add_back(t_redirect **head, t_redirect *new)
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

static t_redirect	*get_redirect(t_list **token_list, t_list *tmp)
{
	t_redirect	*new;

	if (tmp == NULL)
	{
		new = new_redirect(NULL, (*token_list)->content);
		free((*token_list)->content);
		free(*token_list);
		*token_list = tmp;
	}
	else
	{
		new = new_redirect(tmp->content, (*token_list)->content);
		free((*token_list)->content);
	}
	return (new);
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
			new = get_redirect(token_list, tmp);
			free(*token_list);
			*token_list = tmp;
			redirect_add_back(&redirect, new);
		}
		if ((*token_list) != NULL)
			tmp = (*token_list)->next;
		free(*token_list);
		*token_list = tmp;
	}
	return (redirect);
}
