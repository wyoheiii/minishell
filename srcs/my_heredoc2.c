#include "minishell.h"


bool	set_heredoc(t_parsed *parsed, t_envlist *lst)
{
    t_redirect	*red;

    red = parsed->redirect;
    while (parsed != NULL)
    {
        while (red != NULL)
        {
            if (red->state == HERE_DOCUMENT)
            {
                if (my_heredoc(red, lst) != 0)
                    return (false);
            }
            red = red->next;
        }
        if (parsed->next != NULL)
            red = parsed->next->redirect;
        parsed = parsed->next;
    }
    return (true);
}