#include "utils.h"

bool	ft_isspace(char ch)
{
	if ((ch >= '\a' && ch <= '\r') || ch == ' ')
		return (true);
	return (false);
}
