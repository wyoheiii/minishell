#include "flag.h"

void	set_flag(unsigned char *flags, const size_t bit)
{
	(*flags) |= bit;
}

void	unset_flag(unsigned char *flags, const size_t bit)
{
	(*flags) &= ~bit;
}

bool	check_flag(const unsigned char flags, const size_t bit)
{
	if (flags & bit)
		return (true);
	return (false);
}
