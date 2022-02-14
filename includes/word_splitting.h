/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_splitting.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkaneshi <tkaneshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 16:46:07 by tkaneshi          #+#    #+#             */
/*   Updated: 2022/02/14 16:46:07 by tkaneshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORD_SPLITTING_H
# define WORD_SPLITTING_H

# include <stdlib.h>
# include <stdbool.h>

# include "libft.h"
# include "expand_struct.h"
# include "list_utils.h"
# include "utils.h"
# include "libft_utils.h"

# define DELIMITER " \t\n"

t_list	*word_splitting(char *str);
char	*func(t_expand **list, char **line, t_list *split);

#endif
