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
#include "minishell.h"
#include "g_minishell.h"

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

int	builtin_exit(void)
{
	exit_state(1);
	return (0);
}
