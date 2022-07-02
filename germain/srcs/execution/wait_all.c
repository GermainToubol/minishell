/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 16:18:11 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/28 10:41:58 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include "libft.h"
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
	exit_status = 0;
	if (last_pid > 0)
		set_last_pid(last_pid);
	while (i < n_processes)
	{
		status = 0;
		pid = wait(&status);
		if (WIFEXITED(status))
			wait_exited(status, pid, &exit_status, last_pid);
		else if (WIFSIGNALED(status))
			wait_signaled(status, pid, &exit_status, last_pid);
		pid_remove_pid(pid);
		if (pid > 0)
			kill(pid, SIGINT);
		i++;
	}
	return (exit_status);
}

static void	wait_exited(int status, pid_t pid, int *exit_status,
				pid_t last_pid)
{
	if (pid == last_pid || pid == get_last_pid())
	{
		*exit_status = WEXITSTATUS(status);
		set_status(*exit_status);
	}
}

static void	wait_signaled(int status, pid_t pid, int *exit_status,
				pid_t last_pid)
{
	int	sig_number;

	sig_number = WTERMSIG(status);
	if (pid == last_pid || pid == get_last_pid())
	{
		*exit_status = 128 + sig_number;
		set_status(*exit_status);
	}
}
