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
