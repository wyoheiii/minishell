/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyohei <wyohei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 18:17:54 by wyohei            #+#    #+#             */
/*   Updated: 2022/02/12 18:18:04 by wyohei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sig.h"
void sig_heredoc(int sig)
{
    if(sig == SIGINT)
    {
        ft_putstr_fd("\n",1);
        g_status = 1;
        exit(1);
    }
}

void sig_quit(int sig)
{
    if(sig == SIGINT)
    {
        ft_putstr_fd("\n",1);
        g_status = 130;
    }
    if(sig == SIGQUIT)
    {
        ft_putstr_fd("\n",1);
        ft_putstr_fd("Quit: 3\n",1);
        g_status = 131;
    }
}
void command_sig(void)
{
    signal(SIGINT,sig_quit);
    signal(SIGQUIT, sig_quit);
}

void heredoc_sig(void)
{
    signal(SIGINT,sig_heredoc);
    signal(SIGQUIT, SIG_IGN);
}
