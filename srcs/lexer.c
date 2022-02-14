/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkaneshi <tkaneshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 16:43:14 by tkaneshi          #+#    #+#             */
/*   Updated: 2022/02/14 16:43:14 by tkaneshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
