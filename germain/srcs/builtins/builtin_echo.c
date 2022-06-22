/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 10:55:52 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/22 11:25:56 by gtoubol          ###   ########.fr       */
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

	(void)env;
	n_arg = 0;
	i = 1;
	n_arg = check_n_option(argc, argv);
	i += n_arg;
	while (i < argc)
	{
		ft_putstr_fd(argv[i], 1);
		i++;
		if (i < argc)
			ft_putchar_fd(' ', 1);
	}
	if (n_arg == 0)
		ft_putchar_fd('\n', 1);
	if (errno != 0)
	{
		perror("minishell: echo");
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
