/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkaneshi <tkaneshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 16:43:50 by tkaneshi          #+#    #+#             */
/*   Updated: 2022/02/15 16:17:55 by tkaneshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

static bool	is_special_char(const char ch)
{
	if (ch == EOF || ch == '\0' || ch == '<' || ch == '>' || ch == '|')
		return (true);
	else
		return (false);
}

static bool	lookahead_first_char(const char ch, unsigned char *flags)
{
	unset_flag(flags, FIRST_FLAG);
	if (ch == '\'')
		set_flag(flags, QUOTE_FLAG);
	else if (ch == '\"')
		set_flag(flags, DOUBLE_QUOTE_FLAG);
	else if (ch == '$')
		set_flag(flags, VARIABLE_FLAG);
	else if (ch == '<' || ch == '>')
	{
		set_flag(flags, REDIRECT_FLAG);
		return (false);
	}
	else if (ch == '|')
	{
		set_flag(flags, PIPE_FLAG);
		return (false);
	}
	else if (ch == EOF || ch == '\0')
	{
		set_flag(flags, EOF_FLAG);
		return (false);
	}
	return (true);
}

static bool	lookahead(char ch, unsigned char *flags)
{
	if (check_flag((*flags), FIRST_FLAG))
		return (lookahead_first_char(ch, flags));
	else if (check_flag((*flags), QUOTE_FLAG))
	{
		if (ch == '\'')
			unset_flag(flags, QUOTE_FLAG);
	}
	else if (check_flag((*flags), DOUBLE_QUOTE_FLAG))
	{
		if (ch == '\"')
			unset_flag(flags, DOUBLE_QUOTE_FLAG);
	}
	else
	{
		if (ft_isspace(ch) || is_special_char(ch))
			return (false);
		else if (ch == '\'')
			set_flag(flags, QUOTE_FLAG);
		else if (ch == '\"')
			set_flag(flags, DOUBLE_QUOTE_FLAG);
	}
	if (check_flag((*flags), EOF_FLAG))
		return (false);
	return (true);
}

static bool	check_last(const char *line, unsigned char *flags,
		size_t *index, size_t *length)
{
	if (check_flag((*flags), QUOTE_FLAG)
		|| check_flag((*flags), DOUBLE_QUOTE_FLAG))
	{
		(*index) += 1;
		(*length) += 1;
	}	
	if (check_flag((*flags), REDIRECT_FLAG))
	{
		(*index) += 1;
		(*length) += 1;
		if (line[(*length)] == line[((*length) - 1)])
		{
			(*index) += 1;
			(*length) += 1;
		}
	}
	if (check_flag((*flags), PIPE_FLAG))
	{
		(*index) += 1;
		(*length) += 1;
	}
	if (check_flag((*flags), EOF_FLAG))
		return (true);
	return (false);
}

char	*get_token(const char *line, size_t *index, size_t size)
{
	size_t			start;
	size_t			length;
	unsigned char	flags;
	char			*token;

	start = 0;
	while (ft_isspace(line[start]))
	{
		(*index) += 1;
		start += 1;
	}
	if (((*index)) >= size)
		return (NULL);
	length = start;
	flags = '\0';
	set_flag(&flags, FIRST_FLAG);
	while (line[length] != '\0' && lookahead(line[length], &flags))
	{
		(*index) += 1;
		length += 1;
	}
	if (line[length] != '\0' && check_last(line, &flags, index, &length))
		return (NULL);
	token = ft_substr(line, start, (length - start));
	return (token);
}
