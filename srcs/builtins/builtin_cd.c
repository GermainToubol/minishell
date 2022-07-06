/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_in_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 10:19:43 by gtoubol           #+#    #+#             */
/*   Updated: 2022/07/04 16:47:51 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "minishell.h"
#include "g_minishell.h"

/**
   Builtin to change the directory:
   @input:
   * NULL -> go to $HOME
   * relativ/abspath without starting ~

   @output: 0 on sucess, 1 otherwise
 */

static int	cd_errors(int argc, char **argv, t_list *env);
static char	*cd_path_to_go(char *path, t_list *env);
static int	cd_update_env(t_list **env);
static int	cd_change_dir(char *path, t_list **env);

int	builtin_cd(int argc, char **argv, t_list **env)
{
	int		re;
	char	*target;
	char	buffer[4096];

	if (cd_errors(argc, argv, *env) != 0)
		return (1);
	if (argc == 1)
		target = cd_path_to_go(NULL, *env);
	else
		target = cd_path_to_go(argv[1], *env);
	if (target == NULL)
		return (ft_fprintf(2, "minishell: cd: memory allocation\
 error encountered\n"), 1);
	re = cd_change_dir(target, env);
	if (re != 0)
		ft_fprintf(2, "minishell: cd: %s: %s\n", target, strerror(errno));
	if (argv[1] != NULL && ft_strcmp(argv[1], "-") == 0
		&& ft_printf("%s\n", getcwd(buffer, 4096)) < 0)
		return (perror("minishell: cd: write error"), 1);
	return (re);
}

static int	cd_errors(int argc, char **argv, t_list *env)
{
	if (argc > 2)
	{
		ft_fprintf(2, "minishell: cd: too many arguments\n");
		return (1);
	}
	if ((argc == 1 || (argc == 2 && argv[1][0] == '~' && (argv[1][1] == '\0'
			|| argv[1][1] == '/'))) && environment_get(env, "HOME") == NULL)
	{
		ft_fprintf(2, "minishell: cd: HOME not set\n");
		return (1);
	}
	if (argc == 2 && argv[1][0] == '-'
		&& environment_get(env, "OLDPWD") == NULL)
	{
		ft_fprintf(2, "minishell: cd: OLDPWD not set\n");
		return (1);
	}
	return (0);
}

static char	*cd_path_to_go(char *path, t_list *env)
{
	if (path == NULL)
		return (environment_get(env, "HOME"));
	if (path[0] == '-')
		return (environment_get(env, "OLDPWD"));
	return (path);
}

static int	cd_change_dir(char *path, t_list **env)
{
	int		re;
	char	cwd_path[PATH_MAX];

	if (path[0] == '\0')
		return (0);
	if (environment_get(*env, "PWD") == NULL)
	{
		getcwd(cwd_path, PATH_MAX);
		if (environment_add(env, "PWD") == NULL
			|| environment_set(*env, "PWD", cwd_path) == -1)
		{
			ft_fprintf(2, "minishell: cd: memory allocation error\n");
			return (500);
		}
	}
	re = chdir(path);
	if (re == 0)
		return (cd_update_env(env));
	return (1);
}

static int	cd_update_env(t_list **env)
{
	char	cwd_path[PATH_MAX];

	if (environment_get(*env, "OLDPWD") == NULL)
	{
		if (environment_add(env, "OLDPWD") == NULL
			|| environment_set(*env, "OLDPWD", environment_get(*env, "PWD")))
		{
			ft_fprintf(2, "minishell: cd: memory allocation error\n");
			return (500);
		}
	}
	else if (environment_set(*env, "OLDPWD", environment_get(*env, "PWD")) != 0)
	{
		ft_fprintf(2, "minishell: cd: memory allocation error\n");
		return (500);
	}
	getcwd(cwd_path, PATH_MAX);
	if (environment_set(*env, "PWD", cwd_path) == -1)
	{
		ft_fprintf(2, "minishell: cd: memory allocation error\n");
		return (500);
	}
	return (0);
}
