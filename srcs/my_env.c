/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyohei <wyohei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 18:17:03 by wyohei            #+#    #+#             */
/*   Updated: 2022/02/12 19:57:57 by wyohei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_c.h"

int	my_env(t_envlist *envlst)
{
	while (envlst != NULL)
	{
		if (envlst->value != NULL && envlst->value[0] != '\0')
			printf("%s=%s\n", envlst->key, envlst->value);
		envlst = envlst->next;
	}
	g_status = 0;
	return (0);
}
