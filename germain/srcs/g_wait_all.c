/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_wait_all.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 11:51:48 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/09 15:18:00 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <sys/wait.h>
#include <unistd.h>
#include "minishell.h"
#include "g_minishell.h"

static void	g_wait_exited(int status, pid_t pid, int *exit_status, pid_t last_pid);
static void	g_wait_signaled(int status, pid_t pid, int *exit_status, pid_t last_pid);

int	g_wait_all(int n_processes, pid_t last_pid)
{
	int 	i;
	pid_t	pid;
	int		status;
	int		exit_status;

	i = 0;
	while (i < n_processes)
	{
		status = 0;
		pid = wait(&status);
		if (WIFEXITED(status))
		{
			g_wait_exited(status, pid, &exit_status, last_pid);
		}
		else if (WIFSIGNALED(status))
		{
			g_wait_signaled(status, pid, &exit_status, last_pid);
		}
		i++;
	}
	return (exit_status);
}

static void	g_wait_exited(int status, pid_t pid, int *exit_status, pid_t last_pid)
{
	if (pid == last_pid)
	{
		*exit_status = WEXITSTATUS(status);
	}
}

static void	g_wait_signaled(int status, pid_t pid, int *exit_status, pid_t last_pid)
{
	int	sig_number;

	sig_number = WTERMSIG(status);
	if (pid == last_pid)
		*exit_status = 128 + sig_number;
}
