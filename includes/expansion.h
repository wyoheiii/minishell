/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkaneshi <tkaneshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 16:47:39 by tkaneshi          #+#    #+#             */
/*   Updated: 2022/02/14 16:47:40 by tkaneshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

# include <stdlib.h>

# include "libft.h"
# include "minishell_c.h"
# include "parser.h"
# include "expand_struct.h"
# include "expand_argv.h"

# define NONE		0
# define AMBIGUOUS	1
# define SYNTAX		2

void	expansion(t_parsed *parsed, t_envlist *envlist);

#endif
