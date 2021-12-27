#include "token.h"

static bool	is_special_char(const char ch)
{
	if (ch == '\'' || ch == '\"' || ch == EOF
		|| ch == '\0' || ch == '<' || ch == '>' || ch == '|')
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
		set_flag(flags, REDIRECT_FLAG);
	else if (ch == '|')
		set_flag(flags, PIPE_FLAG);
	else if (ch == EOF || ch == '\0')
		set_flag(flags, EOF_FLAG);
	else
		return (false);
	return (true);
}

static bool	lookahead(char ch, unsigned char *flags)
{
	if (check_flag((*flags), FIRST_FLAG))
		lookahead_first_char(ch, flags);
	else if (check_flag((*flags), QUOTE_FLAG))
	{
		if (ch == '\'')
			return (false);
	}
	else if (check_flag((*flags), DOUBLE_QUOTE_FLAG))
	{
		if (ch == '\"')
			return (false);
	}
	else if (check_flag((*flags), REDIRECT_FLAG))
		return (false);
	else if (check_flag((*flags), PIPE_FLAG))
		return (false);
	else
	{
		if (ft_isspace(ch) || is_special_char(ch))
			return (false);
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
		if (line[(*length)] == line[((*length) - 1)])
		{
			(*index) += 1;
			(*length) += 1;
		}
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
	while (lookahead(line[length], &flags))
	{
		(*index) += 1;
		length += 1;
	}
	if (check_last(line, &flags, index, &length))
		return (NULL);
	token = ft_substr(line, start, (length - start));
	return (token);
}
