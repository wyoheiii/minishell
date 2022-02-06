#include "redirect_list.h"

static t_redirect	*new_redirect(char	*filename, char *meta)
{
	t_redirect	*redirect;

	if (filename == NULL && meta != NULL)
	{
		ft_putendl_fd("ambiguous redirect", 2);
		return (NULL);
	}
	redirect = (t_redirect *)malloc(sizeof(t_redirect));
	if (redirect == NULL)
		return (NULL);
	redirect->filename = filename;
	redirect->state = get_state(meta);
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
			if (tmp == NULL)
				return (NULL);
			new = new_redirect(tmp->content, (*token_list)->content);
			free((*token_list)->content);
			free(*token_list);
			*token_list = tmp;
			if (new == NULL)
				return (NULL);
			redirect_add_back(&redirect, new);
		}
		tmp = (*token_list)->next;
		free(*token_list);
		*token_list = tmp;
	}
	new = new_redirect(NULL, NULL);
	redirect_add_back(&redirect, new);
	return (redirect);
}
