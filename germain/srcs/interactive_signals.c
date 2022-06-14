/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactive_signals.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 10:13:48 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/14 13:20:58 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <signal.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include "minishell.h"
#include "g_minishell.h"

static void signal_handler(int signum, siginfo_t *siginfo,
				void *context);

/**
 * Set the signal handler of the minishell in interactive session.
 *
 * In interactive mode, the SIGINT signal will cause all son_processes
 * to recive a SIGINT signal.
 *
 * @return 0 if t
 */

int	init_signal_interactive(struct sigaction *sa)
{
	sa->sa_handler = NULL;
	sigemptyset(&sa->sa_mask);
	sa->sa_flags = SA_SIGINFO;
	sa->sa_sigaction = signal_handler;
	return (sigaction(SIGINT, sa, NULL));
}

static void signal_handler(int signum, siginfo_t *siginfo,
				void *context)
{
	(void)context;
	if (signum != SIGINT)
	{
		ft_fprintf(2, "%s %d\n", "unexpected signal catch:", signum);
		return ;
	}
	ft_printf("%d\n", siginfo->si_pid);
	if (siginfo->si_pid == 0)
	{
		write(1, "Ui\n", 3);
	}
	else
	{
		write(1, "Ok\n", 3);
		//kill(siginfo->si_pid, SIGUSR1);
		exit(EXIT_SUCCESS);
	}
}
