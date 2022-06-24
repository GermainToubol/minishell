/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 16:18:11 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/24 12:48:34 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include "minishell.h"
#include "g_minishell.h"

static void	wait_exited(int status, pid_t pid, int *exit_status,
				pid_t last_pid);
static void	wait_signaled(int status, pid_t pid, int *exit_status,
				pid_t last_pid);

int	wait_all(int n_processes, pid_t last_pid)
{
	int		i;
	pid_t	pid;
	int		status;
	int		exit_status;

	i = 0;
	while (i < n_processes)
	{
		status = 0;
		pid = wait(&status);
		if (WIFEXITED(status))
			wait_exited(status, pid, &exit_status, last_pid);
		else if (WIFSIGNALED(status))
			wait_signaled(status, pid, &exit_status, last_pid);
		i++;
	}
	return (exit_status);
}

static void	wait_exited(int status, pid_t pid, int *exit_status,
				pid_t last_pid)
{
	if (pid == last_pid)
		*exit_status = WEXITSTATUS(status);
}

static void	wait_signaled(int status, pid_t pid, int *exit_status,
				pid_t last_pid)
{
	int	sig_number;

	sig_number = WTERMSIG(status);
	if (pid == last_pid)
		*exit_status = 128 + sig_number;
}
