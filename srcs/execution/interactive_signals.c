/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactive_signals.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 10:13:48 by gtoubol           #+#    #+#             */
/*   Updated: 2022/07/11 10:23:48 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/history.h>
#include <stdio.h>
#include <signal.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include "minishell.h"
#include "g_minishell.h"

static void	signal_handler(int signum);

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
	sa->sa_handler = signal_handler;
	sigemptyset(&sa->sa_mask);
	sa->sa_flags = SA_RESTART;
	sigaction(SIGINT, sa, NULL);
	sigaction(SIGQUIT, sa, NULL);
	return (0);
}

static void	signal_handler(int signum)
{
	int	size;

	if (signum != SIGINT && signum != SIGQUIT)
	{
		ft_fprintf(2, "%s %d\n", "unexpected signal catch:", signum);
		return ;
	}
	if (signum == SIGQUIT || is_father() == 0)
		return ;
	set_status(130);
	set_interupt();
	size = pid_lstlen();
	pid_signal_all();
	wait_all(size, 0);
	write(2, "^C", 2);
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_replace_line("", 1);
	rl_on_new_line();
}
