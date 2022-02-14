/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_param.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkaneshi <tkaneshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 16:45:24 by tkaneshi          #+#    #+#             */
/*   Updated: 2022/02/14 16:45:25 by tkaneshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_PARAM_H
# define EXPAND_PARAM_H

# include <stdbool.h>
# include <stdlib.h>

# include "libft.h"
# include "param.h"
# include "expand_struct.h"
# include "minishell_c.h"

void	expand_join_last(t_expand *new, char *str);
void	expand_joinflag_on(t_expand *new);
void	expand_add_split(t_expand *new, char *param);
bool	add_expanded_param(t_expand *new, t_expand *list, t_envlist *envlist);

#endif