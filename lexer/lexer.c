#include "lexer.h"

static bool	ft_isspace(char ch)
{
	/* Returns true if it is a space character */
	/* Implemented later */
	return (true);
}

static bool	lookahead(char ch, unsigned char *flags)
{
	/* Returns true if the character constitutes a token */
	/* Implemented later */
	return (true);
}

char	*get_token(const char *line, size_t *index)
{
	size_t			length;
	unsigned char	flags;
	char			*token;

	while (ft_isspace(line[(*index)]))
		(*index) += 1;
	length = 0;
	flags = '\0';
	while (lookahead(line[(*index)], &flags))
	{
		(*index) += 1;
		length += 1;
	}
	if (check_flag(flags, EOF_FLAG) && check_flag(NO_TOKEN_FLAG))
		return (NULL);
	token = ft_substr(line, ((*index) - length), length);
	return (token);
}

t_list	*lexer(const char *line)
{
	t_list	*token_list;
	t_list	*current;
	size_t	index;
	char	*token;

	index = 0;
	token_list = ft_lstnew("");
	while (1)
	{
		token = get_token(&(line[index]), &index);
		if (token == NULL)
			break ;
		current = ft_lstnew(token);
		if (current == NULL)
		{
			ft_lstclear(&token_list, free);
			return (NULL);
		}
		ft_lstadd_back(&token_list, current);
		index += ft_strlen(token);
	}
	return (token_list);
}
