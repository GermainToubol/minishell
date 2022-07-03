/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactive_signals.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 10:13:48 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/28 15:58:07 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <signal.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include "minishell.h"
#include "g_minishell.h"

static void	signal_handler(int signum, siginfo_t *siginfo, void *context);

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
	sigaddset(&sa->sa_mask, SIGINT);
	sa->sa_flags = SA_SIGINFO;
	sa->sa_sigaction = signal_handler;
	sigaction(SIGINT, sa, NULL);
	sigaction(SIGQUIT, sa, NULL);
	return (0);
}

static void	signal_handler(int signum, siginfo_t *siginfo, void *context)
{
	int	size;

	(void)context;
	if (signum != SIGINT && signum != SIGQUIT)
	{
		ft_fprintf(2, "%s %d\n", "unexpected signal catch:", signum);
		return ;
	}
	if (signum == SIGQUIT)
		return ;
	size = pid_lstlen();
	pid_signal_all();
	set_interupt();
	wait_all(size, 0);
	if (rl_outstream == stderr)
		write(2, "\n", 1);
	else
		write(1, "\n", 1);
	if (siginfo->si_pid != 0)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	(void)siginfo;
}
