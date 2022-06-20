/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_pipe_series.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 15:42:09 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/20 10:12:02 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>
#include <stdlib.h>
#include "libft.h"
#include "parser.h"
#include "minishell.h"
#include "g_minishell.h"

static void	init_pipe(int *pipe_fds);

int	run_pipe_series(t_parse **parse, char **env)
{
	int		n_parse;
	int		n_process;
	int		pfd[2];
	pid_t	pid;

	n_parse = 0;
	n_process = 0;
	pid = 1;
	init_pipe(pfd);
	while (parse[n_parse] != NULL && pid > 0)
	{
		if (parse[n_parse]->type == PIPE)
			set_outpipe(pfd);
		if (parse[n_parse]->type == CMD)
			parse->;
		n_parse++;
	}
	if (pid > 0)
		return(wait_all(n_process, pid));
	else
		exit(EXIT_FAILURE);
	return (0);
}

static void	init_pipe(int *pipe_fds)
{
	pipe_fds[0] = -2;
	pipe_fds[1] = -2;
}
