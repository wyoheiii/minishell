/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   not_param_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkaneshi <tkaneshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 16:43:32 by tkaneshi          #+#    #+#             */
/*   Updated: 2022/02/14 16:43:32 by tkaneshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "not_param_str.h"

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
