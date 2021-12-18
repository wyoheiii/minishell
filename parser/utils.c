#include "utils.h"

void	lstdel_front(t_list **lst)
{
	t_list		*tmp;

	tmp = (*lst)->next;
	free((*lst));
	(*lst) = tmp;
}
