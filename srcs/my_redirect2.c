#include "minishell.h"
void	hedoc_fd(t_redirect *redirect)
{
	if (redirect->fd > 0)
	{
		my_dup2(redirect->fd, 0);
		my_close(redirect->fd);
	}
	redirect->fd = -1;
}
