/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkaneshi <tkaneshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 16:43:07 by tkaneshi          #+#    #+#             */
/*   Updated: 2022/02/14 20:47:48 by tkaneshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

bool	exist_quote(char *str)
{
	size_t	index;

	if (str == NULL)
		return (false);
	index = 0;
	while (str[index] != '\0')
	{
		if (str[index] == '\'' || str[index] == '\"')
			return (true);
		index += 1;
	}
	return (false);
}

t_expand	*quote_remove_for_eol(t_expand *expand)
{
	size_t		index;
	t_expand	*new;

	index = 0;
	while (expand->argv[index] != '\0')
	{
		if (set_quote_flag(expand, index))
			quote_remove(expand->argv, index);
		index += 1;
	}
	new = expand_new(my_strdup(expand->argv));
	return (new);
}

void	expand_redirect(t_redirect	*redirect, t_envlist *envlist)
{
	t_expand	*expand;
	t_expand	*new;

	while (redirect != NULL)
	{
		expand = expand_new(my_strdup(redirect->filename));
		if (redirect->state == HERE_DOCUMENT)
			new = quote_remove_for_eol(expand);
		else
			new = expand_argv(expand, envlist);
		free_expand(&expand);
		redirect->quote = exist_quote(redirect->filename);
		if (expand_lst_size(new) != 1)
			redirect->is_error = AMBIGUOUS;
		else if (redirect->filename != NULL && redirect->filename[0] != '\0')
		{
			free(redirect->filename);
			redirect->filename = my_strdup(new->argv);
		}
		if (is_delimiter(redirect->filename))
			redirect->is_error = SYNTAX;
		free_expand(&new);
		redirect = redirect->next;
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
		new_command[index] = my_strdup(tmp->argv);
		index += 1;
		tmp = tmp->next;
	}
	new_command[index] = NULL;
	return (new_command);
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
		expand_redirect(parsed->redirect, env);
		free_expand(&argv_list);
		size = expand_lst_size(expand_argv_list);
		new_command = create_new_command(expand_argv_list, size);
		free_expand(&expand_argv_list);
		free(parsed->command);
		parsed->command = new_command;
		parsed = parsed->next;
	}
}
