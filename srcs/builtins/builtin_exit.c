/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 11:07:18 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/27 15:16:43 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "utils.h"
#include "minishell.h"
#include "g_minishell.h"
#include <stdio.h>

static int	exit_state(int i)
{
	static int	is_done = 0;

	if (i > 0)
		is_done = 1;
	return (is_done);
}

int	get_exit_state(void)
{
	return (exit_state(0));
}

static int	exit_check_numeric(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] != '\0')
	{
		ft_fprintf(2, "minishell: exit: %s: numeric argument required\n",
			str);
		set_status(2);
		return (2);
	}
	return (0);
}

static int	exit_check_number(char *str)
{
	long long	n;
	int			status;
	size_t		i;

	i = 0;
	n = ft_atoll_protected(str);
	if (n == 0)
	{
		status = 1;
		while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
			i++;
		if (str[i] == '+' || str[i] == '-')
			i++;
		while (str[i++] == '0')
			status = 0;
		while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
			i++;
	}
	if (n != 0 || (n == 0 && (status == 0 && str[i] == '\0')))
		return (set_status(n), 0);
	ft_fprintf(2, "minishell: exit: %s: numeric argument required\n", str);
	return (set_status(2), 2);
}

int	builtin_exit(int argc, char **argv, t_list **env)
{
	(void)env;
	exit_state(1);
	if (argc == 1)
	{
		exit_state(1);
		return (0);
	}
	if (exit_check_numeric(argv[1]) != 0)
		return (2);
	if (exit_check_number(argv[1]) != 0)
		return (2);
	if (argc > 2)
	{
		ft_fprintf(2, "minishell: exit: too many arguments\n");
		set_status(1);
		return (1);
	}
	return (get_status());
}
