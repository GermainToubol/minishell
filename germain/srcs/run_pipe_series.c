/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_pipe_series.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 15:42:09 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/14 16:26:05 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>
#include <stdlib.h>
#include "libft.h"
#include "minishell.h"
#include "g_minishell.h"

static void	init_pipe(int (*pipe_fds)[2]);

int	run_pipe_series(t_list *execline, char **env)
{
	int		n_processes;
	pid_t	pid;
	int		pipe_fds[2][2];

	n_processes = 0;
	pid = 1;
	init_pipe(pipe_fds);
	while (execline != NULL && pid != 0)
	{
		set_outpipe(execline, pipe_fds[(n_processes + 1) % 2]);
		pid = exec_process(execline, env, pipe_fds[n_processes % 2],
				pipe_fds[(n_processes + 1) % 2]);
		n_processes++;
		clear_exec(&execline, pid);
	}
	if (pid > 0)
		return (wait_all(n_processes, pid));
	else
		exit(EXIT_FAILURE);
	return (1);
}

static void	init_pipe(int (*pipe_fds)[2])
{
	pipe_fds[0][0] = -2;
	pipe_fds[0][1] = -2;
	pipe_fds[1][0] = -2;
	pipe_fds[1][1] = -2;
}
