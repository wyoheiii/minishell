/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyohei <wyohei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 22:55:51 by wyohei            #+#    #+#             */
/*   Updated: 2022/02/14 23:06:53 by wyohei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIG_H
# define SIG_H

# include <signal.h>
# include "minishell.h"
void	signal_ctrl_c(int sig);
void	heredoc_sig(void);
void	catch_signal(void);
void	catch_sasenai_signal(void);
void	command_sig(void);
void	catch_no_signal(void);

#endif