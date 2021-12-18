#include "utils.h"

void	lstdel_front(t_list **lst)
{
	t_list		*tmp;

	tmp = (*lst)->next;
	free((*lst)->content);
	free((*lst));
	(*lst) = tmp;
}

bool	ft_isspace(char ch)
{
	if ((ch >= '\a' && ch <= '\r') || ch == ' ')
		return (true);
	return (false);
}
