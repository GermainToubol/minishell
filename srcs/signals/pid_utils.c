/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 02:32:03 by fmauguin          #+#    #+#             */
/*   Updated: 2022/07/04 02:32:04 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minishell.h"
#include "g_minishell.h"
#include <stdio.h>

int	pid_extend_list(pid_t pid)
{
	return (manage_pid_list(pid, 1));
}

int	pid_signal_all(void)
{
	return (manage_pid_list(0, 2));
}

int	pid_clear_list(void)
{
	return (manage_pid_list(0, -2));
}

int	pid_remove_pid(pid_t pid)
{
	return (manage_pid_list(pid, -1));
}

int	pid_lstlen(void)
{
	return (manage_pid_list(0, 3));
}
