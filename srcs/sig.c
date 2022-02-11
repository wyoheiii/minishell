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
//              bash-3.2$ cat << a　ctrl d 溜まったっやつ出力
//              > w
//              > w
//              bash-3.2$ cat << a
//              > a
//              bash-3.2$ cat << a ctrl c 何も出力しない
//              > w
//              >
//              bash-3.2$
//ctrl d = 0;
//ctrl c = 1>
void sig_heredoc(int sig)
{
    if(sig == SIGINT)
    {
        //rl_on_new_line();
        //rl_replace_line("", 0);
        ft_putstr_fd("\n",2);
        g_status = 1;
        exit(0);
    }

}
void heredoc_sig(void)
{

    //%~ %#;

    signal(SIGINT,sig_heredoc);

    signal(SIGQUIT, SIG_IGN);
    //signal();
}
