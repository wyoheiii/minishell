/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   snytax_err.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyohei <wyohei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 23:13:12 by wyohei            #+#    #+#             */
/*   Updated: 2022/02/25 12:59:26 by wyohei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_c.h"
int	print_syntax_err(char *err)
{
	ft_putstr_fd("minishell: syntax error near unexpected token", 2);
	ft_putstr_fd("`", 2);
	ft_putstr_fd(err, 2);
	ft_putendl_fd("'", 2);
	g_status = 2;
	return (-1);
}

int	syntax_check2(t_parsed *parsed)
{
	if (parsed->redirect->is_error == SYNTAX)
		return (print_syntax_err("newline"));
	if (parsed->redirect->filename == NULL)
		return (print_syntax_err("newline"));
	return (0);
}

int	syntax_check(t_parsed *parsed)
{
	int	i;

	i = 0;
	while (parsed != NULL)
	{
		// if (parsed->command[0] == NULL && parsed->redirect == NULL \
		// && i == 0 && parsed->state == PIPE)
		if (parsed->command[0] == NULL && parsed->redirect == NULL \
		 && parsed->state == PIPE)
			return (print_syntax_err("|"));
		else if ((parsed->next == NULL && parsed->state == PIPE))
			return (print_syntax_err("|"));
		else if (parsed->redirect != NULL && syntax_check2(parsed) == -1)
			return (-1);
		parsed = parsed->next;
		i++;
	}
	return (0);
}
