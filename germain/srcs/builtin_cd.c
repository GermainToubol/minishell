/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_in_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 10:19:43 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/15 18:22:40 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "minishell.h"
#include "g_minishell.h"

static int	cd_errors(int argc, char **env);

/**
   Builtin to change the directory:
   @input:
   * NULL -> go to $HOME
   * relativ/abspath without starting ~
   * relativ path starting with ~

   @output: 0 on sucess, 1 otherwise
 */

int	builtin_cd(int argc, char **argv, char **env)
{
	int	re;

	if (cd_errors(argc, env) != 0)
		return (1);
	if (argc == 1)
		re = chdir(environment_get(env, "HOME"));
	else
		re = chdir(argv[1]);
	if (re != 0)
		ft_fprintf(2, "minishell: cd: %s: %s\n", argv[1], strerror(errno));
	return (re);
}

static int	cd_errors(int argc, char **env)
{
	if (argc > 2)
	{
		ft_fprintf(2, "minishell: cd: too many arguments\n");
		return (1);
	}
	if ((argc == 1 || (argc == 2 && argv[1][0] == '~'))
		&& environment_get(env, "HOME") == NULL)
	{
		ft_fprintf(2, "minishell: cd: HOME not set\n");
		return (1)
	}
	return (0);
}
