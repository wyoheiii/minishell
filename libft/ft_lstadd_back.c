#include "libft.h"
void	ft_lstadd_back(t_list	**lst, t_list	*new)
{
	t_list	*tmp;

	if (lst == NULL)
		return ;
	if (*lst != NULL)
	{
		tmp = ft_lstlast(*lst);
		tmp->next = new;
	}
	else
		*lst = new;
}
