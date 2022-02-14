/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkaneshi <tkaneshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 16:46:01 by tkaneshi          #+#    #+#             */
/*   Updated: 2022/02/14 16:46:01 by tkaneshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>

# include "libft.h"
# include "flag.h"
# include "utils.h"

char	*get_token(const char *line, size_t *index, size_t size);

#endif
