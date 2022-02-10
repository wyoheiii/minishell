#ifndef MY_REDIRECT_H
#define MY_REDIRECT_H
# include <fcntl.h>
# include "minishell.h"
void select_redirect(t_redirect *redirect);
void my_heredoc(t_redirect *redirect);
void set_heredoc(t_parsed *parsed);
#endif
