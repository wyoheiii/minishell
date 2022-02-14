/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkaneshi <tkaneshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 16:45:56 by tkaneshi          #+#    #+#             */
/*   Updated: 2022/02/14 16:45:57 by tkaneshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUOTE_H
# define QUOTE_H

# include <stdbool.h>
# include <stdlib.h>

# include "libft.h"
# include "expand_struct.h"

bool	set_quote_flag(t_expand *list, size_t index);
void	quote_remove(char *str, size_t start);

#endif
