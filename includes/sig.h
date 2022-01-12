#ifndef SIG_H
#define SIG_H

#include <signal.h>
#include "minishell.h"
void signal_ctrl_c(int sig);
void catch_signal(void);
#endif // !1