/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 10:55:52 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/27 14:42:53 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <errno.h>
#include <stdio.h>
#include "libft.h"
#include "minishell.h"
#include "g_minishell.h"

static int	check_n_option(int argc, char **argv);

int	builtin_echo(int argc, char **argv, t_list **env)
{
	int	n_arg;
	int	i;
	int	status;

	(void)env;
	i = 1;
	n_arg = check_n_option(argc, argv);
	i += n_arg;
	status = 0;
	while (i < argc && status >= 0)
	{
		status = ft_printf("%s", argv[i]);
		i++;
		if (i < argc && argv[i][0] != '\0' && argv[i - 1][0] != '\0')
			status = ft_printf(" ");
	}
	if (n_arg == 0)
		status = ft_printf("\n");
	if (status < 0)
	{
		perror("minishell: echo: write error");
		return (1);
	}
	return (0);
}

static int	check_n_option(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 1;
		if (argv[i][0] != '-')
			return (i - 1);
		while (argv[i][j] != '\0')
		{
			if (argv[i][j] != 'n')
				return (i - 1);
			j++;
		}
		i++;
	}
	return (i - 1);
}
