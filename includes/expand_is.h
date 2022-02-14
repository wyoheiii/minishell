/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_is.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkaneshi <tkaneshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 16:45:22 by tkaneshi          #+#    #+#             */
/*   Updated: 2022/02/14 16:45:22 by tkaneshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_IS_H
# define EXPAND_IS_H

# include <stdbool.h>
# include <stdlib.h>

# include "libft.h"
# include "expand_struct.h"

bool	is_remove(t_expand *list);
bool	is_expand(t_expand *list);

#endif
