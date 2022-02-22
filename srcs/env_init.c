/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyohei <wyohei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 18:16:17 by wyohei            #+#    #+#             */
/*   Updated: 2022/02/22 20:45:45 by wyohei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_c.h"
void	create_shlvl(t_envlist **lst, int lvl)
{
	char		*shlvl;
	char		*tmp;
	t_envlist	*new;

	shlvl = ft_itoa(lvl);
	if (!shlvl)
		exit_error("malloc");
	tmp = ft_strjoin("SHLVL=", shlvl);
	if (!tmp)
		exit_error("malloc");
	lst_unset("SHLVL", lst);
	new = env_new(tmp);
	lstadd_back(lst, new);
	free(tmp);
	free(shlvl);
}

void	shlvl_set(t_envlist **lst)
{
	int		lvl;
	char	*sh;

	sh = search_env_key_("SHLVL", *lst);
	if (sh)
	{
		if (sh[0] != '\0')
		{
			if (!check_digit(sh))
			{
				create_shlvl(lst, 1);
				return ;
			}
			lvl = ft_atoi(sh);
			if (lvl == 999)
				lvl = 0;
			create_shlvl(lst, lvl + 1);
			return ;
		}
	}
	create_shlvl(lst, 1);
}

void	env_pwd_set(t_envlist **envlst)
{
	t_envlist	*new;
	char		*char_new;
	char		*pwd;

	if (!key_match_check("OLDPWD", *envlst))
	{
		new = env_new("OLDPWD");
		lstadd_back(envlst, new);
	}
	if (!key_match_check("PWD", *envlst))
	{
		pwd = getcwd(NULL, 0);
		if (!pwd)
		{
			perror("pwd");
			exit(1);
		}
		char_new = ft_strjoin("PWD=", pwd);
		free(pwd);
		new = env_new(char_new);
		lstadd_back(envlst, new);
		free(char_new);
	}
}

void	env_init(char **env, t_envlist **envlst)
{
	size_t		i;
	t_envlist	*new;

	*envlst = NULL;
	if (*env)
		*envlst = env_new(env[0]);
	i = 1;
	while (env[i] != NULL)
	{
		if ((env[i][0] == '_' && env[i][1] == '=') || \
			ft_strncmp(env[i], "OLDPWD=", 7) == 0 )
		{
			i++;
			continue ;
		}
		new = env_new(env[i]);
		lstadd_back(envlst, new);
		i++;
	}
	env_pwd_set(envlst);
	shlvl_set(envlst);
}
