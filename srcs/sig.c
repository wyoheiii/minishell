/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyohei <wyohei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 18:17:51 by wyohei            #+#    #+#             */
/*   Updated: 2022/02/12 18:17:52 by wyohei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sig.h"
//ctrl d de exit syuuryou 
//ctrl c de new line
//ctr
void signal_ctrl_c(int sig)
{
    (void)sig;
    ft_putchar_fd('\n',1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
    g_status = 1;
}

void catch_signal(void)
{
    signal(SIGINT, signal_ctrl_c);
    signal(SIGQUIT, SIG_IGN);
}
void catch_sasenai_signal(void)
{
    signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
}

void no_signal(int sig)
{
    (void)sig;
}

void catch_no_signal(void)
{
    signal(SIGINT, no_signal);
    signal(SIGQUIT, no_signal);
}

