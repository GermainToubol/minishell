/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_clear_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 17:37:58 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/09 18:14:50 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>
#include "libft.h"
#include "minishell.h"
#include "g_minishell.h"

/*
 * g_clear_exec:
 *
 * The execline is used as a virtual stack-like * structure containing
 * each single process to execute. So once it has been executed, the
 * correspondig node is freed.
 */

void	g_clear_exec(t_list **execline, pid_t pid)
{
	if (pid > 0)
	{
		ft_lstpop(execline, tmp_free_cmd);
	}
	else
	{
		ft_lstclear(execline, tmp_free_cmd);
	}
}
