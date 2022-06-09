/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 09:48:12 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/09 14:33:49 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <sys/wait.h>
#include <unistd.h>
#include "libft.h"
#include "minishell.h"
#include "g_minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_list	*execline;
	int		n_processes;
	pid_t	pid;
	int		exit_status;
	int		pipe_fds[2][2] = {{-2}};

	(void)argc;
	(void)argv;
	execline = tmp_init_exec();
	n_processes = 0;
	pid = 1;
	while (execline != NULL && pid != 0)
	{
		g_set_pipe(execline, pipe_fds[(n_processes  + 1) % 2]);
		pid = g_exec_process(execline, env, pipe_fds[n_processes % 2],
				pipe_fds[(n_processes + 1) % 2]);
		n_processes++;
		if (pid > 0)
			ft_lstpop(&execline, tmp_free_cmd);
		else
			ft_lstclear(&execline, tmp_free_cmd);
	}
	if (pid > 0)
		exit_status = g_wait_all(n_processes, pid);
	else
		exit_status = 1;
	return (exit_status);
}
