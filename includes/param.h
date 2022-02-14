/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkaneshi <tkaneshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 16:45:49 by tkaneshi          #+#    #+#             */
/*   Updated: 2022/02/14 16:45:50 by tkaneshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARAM_H
# define PARAM_H

# include <stdlib.h>

# include "libft.h"
# include "expand_struct.h"
# include "minishell_c.h"

char	*get_variable_name(char *line, size_t *start);
char	*param_func(t_expand *list, t_envlist *envlist);

#endif
