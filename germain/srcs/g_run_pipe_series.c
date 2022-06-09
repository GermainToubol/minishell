/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_run_pipe_series.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 17:28:17 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/09 17:44:10 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>
#include "libft.h"
#include "minishell.h"
#include "g_minishell.h"

int	g_run_pipe_series(t_list *execline, char **env)
{
	int		n_processes;
	pid_t	pid;
	int		pipe_fds[2][2];

	n_processes = 0;
	pid = 1;
	while (execline != NULL && pid != 0)
	{
		g_set_pipe(execline, pipe_fds[(n_processes + 1) % 2]);
		pid = g_exec_process(execline, env, pipe_fds[n_processes % 2],
				pipe_fds[(n_processes + 1) % 2]);
		n_processes++;
		g_clear_exec(&execline, pid);
	}
	if (pid > 0)
		return (g_wait_all(n_processes, pid));
	return (1);
}
