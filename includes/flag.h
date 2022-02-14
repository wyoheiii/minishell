/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkaneshi <tkaneshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 16:45:33 by tkaneshi          #+#    #+#             */
/*   Updated: 2022/02/14 16:45:33 by tkaneshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FLAG_H
# define FLAG_H

# include <stdbool.h>
# include <stddef.h>

# define QUOTE_FLAG         1
# define DOUBLE_QUOTE_FLAG  2
# define VARIABLE_FLAG      4
# define REDIRECT_FLAG      8
# define PIPE_FLAG          16
# define EOF_FLAG           32
# define FIRST_FLAG         64

void	set_flag(unsigned char *flags, const size_t bit);
void	unset_flag(unsigned char *flags, const size_t bit);
bool	check_flag(const unsigned char flags, const size_t bit);

#endif
