/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 16:14:13 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/16 16:30:17 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include "libft.h"
#include "minishell.h"
#include "g_minishell.h"

/**
   pwd shows the current working directory.

   @input: any input argument will be ignored.
*/

int	builtin_pwd(int argc, char **argv, t_list **env)
{
	char	path[PATH_MAX];

	(void)argc;
	(void)argv;
	(void)env;
	if (getcwd(path, PATH_MAX) == NULL)
	{
		perror("minishell: pwd");
		return (1);
	}
	ft_printf("%s\n", path);
	return (0);
}
