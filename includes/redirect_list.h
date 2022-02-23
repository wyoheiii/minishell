/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_list.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyohei <wyohei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 16:46:56 by tkaneshi          #+#    #+#             */
/*   Updated: 2022/02/23 20:10:35 by wyohei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECT_LIST_H
# define REDIRECT_LIST_H

# include <stdlib.h>

# include "libft.h"
# include "delimiter.h"

/* state */
# define NONE 			    0
# define PIPE 			    1
# define REDIRECT_INPUT	    2
# define REDIRECT_OUTPUT	3
# define REDIRECT_APPEND	4
# define HERE_DOCUMENT	    5

typedef struct s_redirect
{
	char				*tmpfile;
	int					fd;
	char				*filename;
	int					state;
	int					quote;
	int					is_error;
	struct s_redirect	*next;
}	t_redirect;

t_redirect	*create_redirect(t_list **token_list);

#endif
