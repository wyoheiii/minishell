#include "minishell_c.h"
void	*god_malloc(size_t size)
{
	void	*ret;

	ret = malloc(size);
	if (!ret)
	{
		perror("malloc");
		exit(1);
	}
	return (ret);
}