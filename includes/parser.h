/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkaneshi <tkaneshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 16:45:52 by tkaneshi          #+#    #+#             */
/*   Updated: 2022/02/14 16:45:53 by tkaneshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdbool.h>
# include <stdlib.h>

# include "libft.h"
# include "delimiter.h"
# include "redirect_list.h"
# include "utils.h"

typedef struct s_parsed
{
	char				**command;
	int					state;
	struct s_redirect	*redirect;
	struct s_parsed		*next;
}	t_parsed;

t_parsed	*parser(t_list **token_list);
void		free_parsed(t_parsed **parsed);

#endif
