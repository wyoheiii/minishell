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

void no_signal(int sig)
{
    (void)sig;
}
void catch_sasenai_signal(void)
{
    signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
}
void catch_no_signal(void)
{
    signal(SIGINT, no_signal);
    signal(SIGQUIT, no_signal);
}
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
    //%~ %#cat
//        ^C
//%~ %#echo $?
//130
//%~ %#cat
//^\Quit: 3
//%~ %#echo $?
//131
//sleep 5 | echo hoge
//echo hoge | sleep 5
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
